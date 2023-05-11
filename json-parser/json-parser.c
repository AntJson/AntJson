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
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeTypeString);

            char* valueString = (char*)malloc(sizeof (char) * (value.end - value.start));
            valueString = strncpy(valueString, source + value.start, value.end - value.start);
            child->value.s = valueString;
            addChild(node, child);
            continue;
        }

        if (value.type == JSMN_PRIMITIVE) {
            char* keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
            strncpy(keyValue, source + key.start, key.end - key.start);
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeTypeObject);
            addChild(node, child);

            char* valueString = (char*)malloc(sizeof(char) * (value.end - value.start));
            valueString = strncpy(valueString, source + value.start, value.end - value.start);
            if (valueString[0] == 'n') {
                child->type = JsonNodeTypeNull;
                child->value.s = NULL;
            } else if (valueString[0] == 't') {
                child->type = JsonNodeTypeBool;
                child->value.b = 1;
            } else if (valueString[0] == 'f') {
                child->type = JsonNodeTypeBool;
                child->value.b = 0;
            } else {
                char* stopString;
                if (strstr(valueString, ".")) {
                    child->type = JsonNodeTypeFloat;
                    child->value.f = strtof(valueString, &stopString);
                } else {
                    child->type = JsonNodeTypeInt;
                    child->value.i = (int) strtol(valueString, &stopString, 10);
                }
            }
            continue;
        }

        if (value.type == JSMN_OBJECT) {
            char* keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
            strncpy(keyValue, source + key.start, key.end - key.start);
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeTypeObject);
            addChild(node, child);

            jsmntok_t objectTokens[value.size * 2];
            memcpy(objectTokens, tokens + i + 2, (value.size * 2) * sizeof(*tokens));
            tokensToNodes(objectTokens, value.size * 2, child, source);
            i += (value.size * 2);
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

    node = getEmptyJsonNode("", JsonNodeTypeObject);

    jsmntok_t tokensWithoutRootObject[parsedCount - 1];
    memcpy(tokensWithoutRootObject, tokensParsed + 1, (parsedCount - 1) * sizeof(jsmntok_t));

    tokensToNodes(tokensWithoutRootObject, parsedCount, node, source);
    return node;
}

#endif // DTOCONSTRUCTOR_JSON_PARSER_H