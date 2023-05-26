cmake_minimum_required(VERSION 3.25)
project(AntJson CXX)

set(CMAKE_CXX_STANDARD 11)

set(
        COMMON_SOURCES
        json-node/json.cpp
)

#
# Option for building JSMN parser without parent links
# It will reduce of memory usage and also reduce speed
#
# Check benchmarks of parser (https://lionet.livejournal.com/118853.html)
#
option(JSMN_PARENT_LINKS "Build jsmn_parser with define of building links" "ON")

if (JSMN_PARENT_LINKS STREQUAL "ON")
    set (
        JSMN_PARSER_SRC
            json-parser/json-parser-with-parents.cpp
    )
else ()
    set (
        JSMN_PARSER_SRC
            json-parser/json-parser.cpp
    )
endif()

add_library(AntJson SHARED ${COMMON_SOURCES} ${JSMN_PARSER_SRC})
include_directories(thirdparty/jsmn)

add_subdirectory(test/CLang)
add_subdirectory(test/CppLang)

unset(JSMN_PARENT_LINKS CACHE)