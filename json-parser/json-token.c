//
// Created by danysmall on 5/6/23.
//

#include "json-token.h"
#include "../constants/errors.h"
#include <stdlib.h>

JsonToken* jsonTokenCreate(char* key, char* data, uint32_t childrenLength, JsonToken** children) {
    JsonToken* token = jsonTokenCreateClean();
    jsonTokenUpdateKey(token, key);
    jsonTokenUpdateData(token, data);
    jsonTokenUpdateChildren(token, childrenLength, children);
    return token;
}

JsonToken* jsonTokenCreateClean() {
    JsonToken* token = (JsonToken*)malloc(sizeof(JsonToken));
    return token;
}

void jsonTokenUpdateKey(JsonToken* token, char* key) {
    token->key = key;
}

void jsonTokenUpdateData(JsonToken* token, char* data) {
    token->data = data;
}

int jsonTokenUpdateChildren(JsonToken* token, uint32_t childrenLength, JsonToken** children) {
    int returnCode = 0;
    if (token->children != NULL) {
        for (uint32_t i = 0; i < token->childrenLength; i++) {
            returnCode = jsonTokenFree(token->children[i]);
        }
        free(token->children);
    }
    token->children = children;
    return returnCode;
}

int jsonTokenAddChild(JsonToken* token, JsonToken* child) {
    if (token->children == NULL) {
        if (token->childrenLength != 0) {
            return childrenPtrNullWithNonZeroLength;
        }
        token->children = (JsonToken**)malloc(sizeof (JsonToken*));
        token->children[token->childrenLength++] = child;
        child->parent = token;
        return 0;
    }
    realloc(token->children, sizeof(JsonToken*) * ++token->childrenLength);
    token->children[token->childrenLength - 1] = child;
    return 0;
}

int jsonTokenFree(JsonToken* token) {
    if (token == NULL) {
        return disposeWithNullPtr;
    }
    for (uint32_t i = 0; i < token->childrenLength; i++) {
        int code = jsonTokenFree(token->children[i]);
        if (!code) {
            free(token->children[i]);
        }
    }
    return 0;
}