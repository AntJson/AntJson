//
// Created by danysmall on 5/7/23.
//

#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"

char* getSubstr(const char* source, uint32_t begin, uint32_t end) {
    uint32_t subLength = end-begin;
    uint32_t resultPos = 0;
    char* result = (char*)malloc(sizeof(char) * subLength);

    for (uint32_t i = begin; i < end; i++) {
        result[resultPos++] = source[i];
    }
    return result;
}

JsonToken* jsonTokenFromJsonString(char* source) {
    printf("Json: %s\n", source);

    JsonToken* rootToken = jsonTokenCreateClean();
    Context* context = contextInit();
    contextSetDepth(context, 0);
    contextSetOpenLiteralPos(context, 0);
    contextSetType(context, contextObject);

    uint32_t pos = 0;
    while (source[pos++] != '\0') {
        char currentChar = source[pos];
        if (currentChar == '{') {
            Context* objContext = contextInit();
            contextAddChild(context, objContext);
            context = objContext;
            context->contextType = contextObject;

            JsonToken* objToken = jsonTokenCreateClean();
            jsonTokenAddChild(rootToken, objToken);
            rootToken = objToken;
            continue;
        }
        if (currentChar == '}') {
            context = context->parent;
            continue;
        }
        if (currentChar == '"') {
            if (context->contextType == contextObject) {
                Context* keyContext = contextInit();
                contextAddChild(context, keyContext);
                context = keyContext;

                if (rootToken == NULL) {
                    return NULL;
                }
                if (rootToken->key == NULL || rootToken->children != NULL) {
                    context->contextType = contextKey;
                } else {
                    context->contextType = contextValue;
                }
                context->openLiteralPos = pos;
                continue;
            }
            if (context->contextType == contextKey) {
                if (rootToken->key != NULL) {
                    JsonToken* keyToken = jsonTokenCreateClean();
                    jsonTokenAddChild(rootToken, keyToken);
                    rootToken = keyToken;
                }
                jsonTokenUpdateKey(rootToken, getSubstr(source, context->openLiteralPos, pos + 1));
                context = context->parent;
                printf("Key: %s\n", rootToken->key);
                continue;
            }
            if (context->contextType == contextValue) {
                JsonToken* valueToken = jsonTokenCreateClean();
                jsonTokenAddChild(rootToken, valueToken);
                jsonTokenUpdateData(valueToken, getSubstr(source, context->openLiteralPos, pos + 1));
                printf("Value: %s\n", valueToken->data);
                context = context->parent;
                if (rootToken->parent != NULL) {
                    rootToken = rootToken->parent;
                }
            }
        }
    }
    while(rootToken != NULL && rootToken->parent != NULL) {
        rootToken = rootToken->parent;
    }
    return rootToken;
}