cmake_minimum_required(VERSION 3.25)
project(AntJsonTestCpp CXX)
set(CMAKE_CXX_STANDARD 17)

set (
        COMMON_SOURCES
        dtos/account/account.cpp
        dtos/nvr/nvr.cpp
        ../../third-party/jsmn/jsmn.c
)

set(
        EXECUTABLES
        main.cpp
)

add_executable(AntJsonTestCpp ${COMMON_SOURCES} ${EXECUTABLES})

target_include_directories(
        AntJsonTestCpp
        PUBLIC /home/danysmall/Projects/bitswar/antjson/lib
        PUBLIC ../../third-party
)

target_link_directories(
        AntJsonTestCpp
        PUBLIC /home/danysmall/Projects/bitswar/antjson/cmake-build-debug/lib
)

target_link_libraries(
        AntJsonTestCpp
        PUBLIC -lAntJson
)