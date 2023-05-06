//
// Created by danysmall on 5/6/23.
//
#include <stdint.h>

#ifndef DTOCONSTRUCTOR_JSON_TOKEN_H
#define DTOCONSTRUCTOR_JSON_TOKEN_H

typedef struct __JsonToken_s JsonToken;

struct __JsonToken_s {
    char* key;
    char* data;
    JsonToken** children;
    uint32_t childrenLength;
};

JsonToken* jsonTokenCreate(char* key, char* data, uint32_t childrenLength, JsonToken** children);
JsonToken* jsonTokenCreateClean();

void jsonTokenUpdateKey(JsonToken* token, char* key);
void jsonTokenUpdateData(JsonToken* token, char* data);
int jsonTokenUpdateChildren(JsonToken* token, uint32_t childrenLength, JsonToken** children);
int jsonTokenAddChild(JsonToken* token, JsonToken* child);
int jsonTokenFree(JsonToken* token);

#endif //DTOCONSTRUCTOR_JSON_TOKEN_H
