cmake_minimum_required(VERSION 3.14)
project(zachet2)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
else()
    message(WARNING "OpenMP not found!")
endif()


include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()


set(AVL_TREE src/avltree.hpp src/avltree.cpp)
set(BIN_TREE src/bintree.hpp src/bintree.cpp)
set(GENERATORS src/generators.hpp src/generators.cpp)
# set(DATA_BASE src/data_base.hpp src/data_base.cpp)
set(TESTS_AVL_TREE tests/test_avltree.cpp)
set(TESTS_BIN_TREE tests/test_bintree.cpp)

add_executable(tests_avl ${TESTS_AVL_TREE} ${AVL_TREE})
add_executable(tests_bin ${TESTS_BIN_TREE} ${BIN_TREE})
add_executable(avl_tree src/main_avl.cpp ${AVL_TREE} ${GENERATORS})
add_executable(bin_tree src/main_bin.cpp ${BIN_TREE})

target_link_libraries(tests_avl GTest::gtest_main)
target_link_libraries(tests_bin GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(tests_avl)
gtest_discover_tests(tests_bin)
