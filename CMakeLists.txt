cmake_minimum_required(VERSION 3.25)
project(AntJson C)

set(CMAKE_C_STANDARD 11)

set(
        SOURCE_FILES
        test/main.c
        jsmn/jsmn.c
        json-node/json.c
        json-parser/json-parser.c
        test/structures/user-struct.c
        test/structures/profile-struct.c
        test/structures/contacts-struct.c
)

add_executable(AntJson ${SOURCE_FILES})
#add_library(AntJson SHARED ${SOURCE_FILES})