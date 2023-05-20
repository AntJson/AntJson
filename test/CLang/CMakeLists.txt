cmake_minimum_required(VERSION 3.25)
project(AntJsonTestC C)
set(CMAKE_C_STANDARD 11)

set(
        EXECUTABLES
        main.c
)

add_executable(AntJsonTestC ${EXECUTABLES})

target_include_directories(
        AntJsonTestC
        PUBLIC /home/danysmall/Projects/bitswar/antjson/lib
)

target_link_directories(
        AntJsonTestC
        PUBLIC /home/danysmall/Projects/bitswar/antjson/cmake-build-debug/lib
)

target_link_libraries(
        AntJsonTestC
        PUBLIC -lAntJson
)