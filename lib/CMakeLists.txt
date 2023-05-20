cmake_minimum_required(VERSION 3.25)
project(AntJson CXX)

set(CMAKE_CXX_STANDARD 11)

set(
        COMMON_SOURCES
        json-node/json.cpp
        json-parsers/jsmn-parser/jsmn-parser.cpp
        ../third-party/jsmn/jsmn.c
)

add_library(AntJson SHARED ${COMMON_SOURCES})

target_include_directories(
        AntJson
        PUBLIC ../third-party
)
