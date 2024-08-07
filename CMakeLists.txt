cmake_minimum_required(VERSION 3.23)
project(search_engine)

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)

#[[include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)]]


set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

add_subdirectory(src)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)