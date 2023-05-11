cmake_minimum_required(VERSION 3.25)
project(AntJson C)
set(AntJsonTestBuild_C_LANG 11)

set (
        COMMON_SOURCES
        ../../jsmn/jsmn.c
        ../../json-node/json.c
        ../../json-parser/json-parser.c
)

set(
        EXECUTABLES
        main.c
)
add_executable(AntJsonTestBuild_C_LANG ${COMMON_SOURCES} ${EXECUTABLES})