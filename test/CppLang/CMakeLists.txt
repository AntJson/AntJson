cmake_minimum_required(VERSION 3.25)
project(AntJsonTestBuild_CPP_LANG CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set (
        COMMON_SOURCES
        ../../jsmn/jsmn.c
        ../../json-node/json.c
        ../../json-parser/json-parser.c
        dtos/account/account.cpp
        dtos/nvr/nvr.cpp
)

set(
        EXECUTABLES
        main.cpp
)
add_executable(AntJsonTestBuild_CPP_LANG ${COMMON_SOURCES} ${EXECUTABLES})
