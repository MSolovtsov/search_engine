cmake_minimum_required(VERSION 3.23)
project(search_engine)

set(CMAKE_CXX_STANDARD 20)

set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(nlohmann_json)


set(MY_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
set(MY_SRC_DIR ${CMAKE_SOURCE_DIR}/src/)

add_subdirectory(src)
add_subdirectory(test)

# Создать директорию json в каталоге сборки
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/json)

# Собираем все .json файлы из подкаталога json
file(GLOB JSON_FILES "${CMAKE_SOURCE_DIR}/json/*.json")

# Копировать каждый .json файл в подкаталог json в каталоге сборки
foreach(JSON_FILE ${JSON_FILES})
    get_filename_component(FILE_NAME ${JSON_FILE} NAME)
    configure_file(${JSON_FILE} ${CMAKE_BINARY_DIR}/json/${FILE_NAME} COPYONLY)
endforeach()


# Создаем директорию resources в каталоге сборки
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/resources)

# Собираем все файлы из директории resources
file(GLOB RESOURCE_FILES "${CMAKE_SOURCE_DIR}/resources/*")

# Копируем каждый файл в подкаталог resources в каталоге сборки
foreach(RESOURCE_FILE ${RESOURCE_FILES})
    get_filename_component(FILE_NAME ${RESOURCE_FILE} NAME)  # Извлекаем имя файла
    configure_file(${RESOURCE_FILE} ${CMAKE_BINARY_DIR}/resources/${FILE_NAME} COPYONLY)
endforeach()


target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json)
