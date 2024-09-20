cmake_minimum_required(VERSION 3.23)

enable_testing()
add_subdirectory(googletest)


add_executable(search_engine_test
        test_InvertedIndex.cpp test_SearchServer.cpp
        ${MY_SRC_DIR}InvertedIndex.cpp ${MY_SRC_DIR}SearchServer.cpp
        ${MY_INCLUDE_DIR}InvertedIndex.h ${MY_INCLUDE_DIR}SearchServer.h
        )

include_directories(${MY_INCLUDE_DIR})
include_directories(${MY_SRC_DIR})

target_include_directories(search_engine_test PUBLIC ${MY_INCLUDE_DIR})
target_include_directories(search_engine_test PUBLIC ${MY_SRC_DIR})

target_link_libraries(search_engine_test PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(search_engine_test)