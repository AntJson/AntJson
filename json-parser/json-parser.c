//
// Created by danysmall on 5/11/23.
//
#include "../json-node/json.h"
#include "../jsmn/jsmn.h"
#ifndef DTOCONSTRUCTOR_JSON_PARSER_H
#define DTOCONSTRUCTOR_JSON_PARSER_H

uint32_t tokensToNodes(jsmntok_t* tokens, uint32_t tokensCount, JsonNode* node, const char* source) {
    for (uint32_t i = 0; i < tokensCount; i += 2) {
        jsmntok_t key = tokens[i];
        jsmntok_t value = tokens[i + 1];

        if (value.type == JSMN_STRING) {
            char* keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
            strncpy(keyValue, source + key.start, key.end - key.start);
            JsonNode* child = getEmptyJsonNode(keyValue,string);

            char* valueString = (char*)malloc(sizeof (char) * (value.end - value.start));
            valueString = strncpy(valueString, source + value.start, value.end - value.start);
            child->value.s = valueString;
            addChild(node, child);
            continue;
        }

        if (value.type == JSMN_PRIMITIVE) {
            char* keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
            strncpy(keyValue, source + key.start, key.end - key.start);
            JsonNode* child = getEmptyJsonNode(keyValue,object);
            addChild(node, child);

            char* valueString = (char*)malloc(sizeof(char) * (value.end - value.start));
            valueString = strncpy(valueString, source + value.start, value.end - value.start);
            if (valueString[0] == 'n') {
                child->type = null;
                child->value.s = NULL;
            } else if (valueString[0] == 't') {
                child->type = bool;
                child->value.b = 1;
            } else if (valueString[0] == 'f') {
                child->type = bool;
                child->value.b = 0;
            } else {
                char* stopString;
                if (strstr(valueString, ".")) {
                    child->type = number_f;
                    child->value.f = strtof(valueString, &stopString);
                } else {
                    child->type = number_i;
                    child->value.i = (int) strtol(valueString, &stopString, 10);
                }
            }
            continue;
        }

        if (value.type == JSMN_OBJECT) {
            char* keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
            strncpy(keyValue, source + key.start, key.end - key.start);
            JsonNode* child = getEmptyJsonNode(keyValue,object);
            addChild(node, child);

            jsmntok_t objectTokens[tokensCount - i];
            memcpy(objectTokens, tokens + i + 2, (tokensCount - i - 1) * sizeof(*tokens));
            i += tokensToNodes(objectTokens, tokensCount - i - 1, child, source);
            continue;
        }
    }
    return tokensCount;
}

JsonNode* jsonNodeParse(const char* source) {
    JsonNode* node = NULL;

    jsmn_parser parser;
    jsmntok_t tokensParsed[128];
    jsmn_init(&parser);

    int parsedCount = jsmn_parse(&parser, source, strlen(source), tokensParsed, 128);
    if (parsedCount <= 0) {
        return node;
    }

    node = getEmptyJsonNode("", object);

    jsmntok_t tokensWithoutRootObject[128];
    memcpy(tokensWithoutRootObject, tokensParsed + 1, (parsedCount - 1) * sizeof(jsmntok_t));

    tokensToNodes(tokensWithoutRootObject, parsedCount, node, source);
    return node;
}

#endif // DTOCONSTRUCTOR_JSON_PARSER_H