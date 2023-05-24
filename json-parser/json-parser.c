//
// Created by danysmall on 5/11/23.
//
#include "../json-node/json.h"
#include "../jsmn/jsmn.h"
#ifndef DTOCONSTRUCTOR_JSON_PARSER_H
#define DTOCONSTRUCTOR_JSON_PARSER_H

char* getSubstr(const char* source, int start, int end) {
    char* value = (char*)malloc(sizeof(char) * (end - start) + 1);
    strncpy(value, source + start, end - start);
    value[end - start] = '\0';
    return value;
}

uint32_t tokensToNodes(jsmntok_t* tokens, uint32_t tokensCount, JsonNode* node, const char* source) {
    uint8_t multiplier = 2;
    if (node->type == JsonNodeTypeArray) {
        multiplier = 1;
    }
    for (uint32_t i = 0; i < tokensCount; i += multiplier) {
        jsmntok_t key;
        jsmntok_t value;
        if (node->type == JsonNodeTypeArray) {
            key = tokens[i];
            value = tokens[i];
        } else {
            key  = tokens[i];
            value = tokens[i + 1];
        }

        if (value.type == JSMN_STRING) {
            if (node->type == JsonNodeTypeArray) {
                JsonNode* child = getEmptyJsonNode("",JsonNodeTypeString);

                char* valueString = getSubstr(source, value.start, value.end);
                addValueString(child, valueString);
                free(valueString);
                addChild(node, child);

                continue;
            }
            char* keyValue = getSubstr(source, key.start, key.end);
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeTypeString);
            free(keyValue);

            char* valueString = getSubstr(source, value.start, value.end);
            addValueString(child, valueString);
            free(valueString);
            addChild(node, child);
            continue;
        }

        if (value.type == JSMN_PRIMITIVE) {
            if (node->type == JsonNodeTypeArray) {
                JsonNode* child = getEmptyJsonNode("",JsonNodeTypeString);

//                char* valueString = (char*)malloc(sizeof (char) * (value.end - value.start));
//                valueString = strncpy(valueString, source + value.start, value.end - value.start);
                char* valueString = getSubstr(source, value.start, value.end);
                addChild(node, child);

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
                    char* stopString = NULL;
                    if (strstr(valueString, ".")) {
                        child->type = JsonNodeTypeFloat;
                        child->value.f = strtof(valueString, &stopString);
                    } else {
                        child->type = JsonNodeTypeInt;
                        child->value.i = (int) strtol(valueString, &stopString, 10);
                    }
                }
                free(valueString);
                continue;
            }

            char* keyValue = getSubstr(source, key.start, key.end);
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeTypeObject);
            free(keyValue);
            addChild(node, child);

            char* valueString = getSubstr(source, value.start, value.end);
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
            free(valueString);
            continue;
        }

        if (value.type == JSMN_OBJECT) {
            JsonNode* child;
            if (node->type ==  JsonNodeTypeArray) {
                child = getEmptyJsonNode("",JsonNodeTypeObject);
            } else {
                char* keyValue = getSubstr(source, key.start, key.end);
                child = getEmptyJsonNode(keyValue,JsonNodeTypeObject);
                free(keyValue);
            }
            addChild(node, child);

            jsmntok_t objectTokens[value.size * 2];
            memcpy(objectTokens, tokens + i + multiplier, (value.size * 2) * sizeof(jsmntok_t));
            tokensToNodes(objectTokens, value.size * 2, child, source);
            i += (value.size * 2);
            continue;
        }

        if (value.type == JSMN_ARRAY) {
            uint32_t arrayNodesCount = 0;
            for (uint32_t j = i + 1; j < tokensCount; j++) {
                if (tokens[j].start >= value.end) {
                    break;
                }
                arrayNodesCount++;
            }
            arrayNodesCount--;

            char* keyValue = getSubstr(source, key.start, key.end);
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeTypeArray);
            free(keyValue);
            addChild(node, child);

            jsmntok_t objectTokens[arrayNodesCount];
            memcpy(objectTokens, tokens + i + 2, (arrayNodesCount) * sizeof(jsmntok_t));
            tokensToNodes(objectTokens, arrayNodesCount, child, source);
            i += (arrayNodesCount);

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

    tokensToNodes(tokensWithoutRootObject, parsedCount - 1, node, source);
    return node;
}

#endif // DTOCONSTRUCTOR_JSON_PARSER_H