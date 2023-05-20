cmake_minimum_required(VERSION 3.25)
project(AntJson CXX)

set(CMAKE_CXX_STANDARD 11)

set(
        COMMON_SOURCES
        json-node/json.c
        json-parser/json-parser.c
        ../third-party/jsmn/jsmn.c
)

add_library(AntJson SHARED ${COMMON_SOURCES})