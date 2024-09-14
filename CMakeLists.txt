cmake_minimum_required(VERSION 3.23)
project(search_engine)

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)


set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src/)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
