cmake_minimum_required(VERSION 3.25)
project(AntJsonTestBuild_CPP_LANG CXX)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set (
        COMMON_SOURCES
        dtos/account/account.cpp
        dtos/nvr/nvr.cpp
)

set(
        EXECUTABLES
        main.cpp
)
add_executable(AntJsonTestBuild_CPP_LANG ${COMMON_SOURCES} ${EXECUTABLES})

include_directories(
        AntJsonTestBuild_CPP_LANG
        ../../
)

target_link_options(
        AntJsonTestBuild_CPP_LANG
        PUBLIC -Wl,--no-as-needed -Wl,--export-dynamic
)

target_link_directories(
        AntJsonTestBuild_CPP_LANG
        PUBLIC ../../cmake-build-debug
)

target_link_libraries(
        AntJsonTestBuild_CPP_LANG
        PUBLIC -lAntJson
)
