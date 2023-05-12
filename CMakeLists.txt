cmake_minimum_required(VERSION 3.25)
project(AntJson C)

set(CMAKE_C_STANDARD 11)

set(
        COMMON_SOURCES
        jsmn/jsmn.c
        json-node/json.c
        json-parser/json-parser.c
)

add_library(AntJson SHARED ${COMMON_SOURCES})

add_subdirectory(test/CLang)
add_subdirectory(test/CppLang)