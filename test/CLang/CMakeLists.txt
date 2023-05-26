cmake_minimum_required(VERSION 3.25)
project(AntJson C)
set(AntJsonTestBuild_C_LANG 11)

set (
        COMMON_SOURCES
        ../../json-node/json.cpp
        ../../json-parser/json-parser.cpp
)

set(
        EXECUTABLES
        main.c
)
add_executable(AntJsonTestBuild_C_LANG ${COMMON_SOURCES} ${EXECUTABLES})
include_directories(../../thirdparty/jsmn)