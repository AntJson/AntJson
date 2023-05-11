cmake_minimum_required(VERSION 3.25)
project(DTOConstructor C)

set(CMAKE_C_STANDARD 11)

set(
        SOURCE_FILES
        main.c
        constants/errors.h
        complexity-tests/simple-struct.c
        complexity-tests/nested-structs.c
        json-node/json.c
        json-parser/json-token.c
        json-parser/json-token-test.c
        json-parser/context/context.c
        json-parser/tokenizer/tokenizer.c
        json-parser/node-converter/node-converter.c
        jsmn/jsmn.h
)

add_executable(DTOConstructor ${SOURCE_FILES})
