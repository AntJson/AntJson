cmake_minimum_required(VERSION 3.25)
project(DTOConstructor C)

set(CMAKE_C_STANDARD 11)

set(
        SOURCE_FILES
        main.c
        complexity-tests/simple-struct.c
        complexity-tests/nested-structs.c
        json-node/json.c
        json-parser/json-token.c
        json-parser/json-token-test.c
        constants/errors.h)

add_executable(DTOConstructor ${SOURCE_FILES})
