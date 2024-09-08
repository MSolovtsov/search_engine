cmake_minimum_required(VERSION 3.23)


add_executable(search_engine
        main.cpp ConverterJSON.cpp InvertedIndex.cpp
        ${MY_INCLUDE_DIR}ConverterJSON.h ${MY_INCLUDE_DIR}InvertedIndex.h)

include_directories(${MY_INCLUDE_DIR})

target_include_directories(search_engine PUBLIC ${MY_INCLUDE_DIR})


