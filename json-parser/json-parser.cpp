//
// Created by danysmall on 5/11/23.
//
#include "../json-node/json.h"
#include <jsmn.h>

using namespace Ant;

char* getSubstr(const char* source, int start, int end) {
    char* value = (char*)malloc(sizeof(char) * (end - start) + 1);
    strncpy(value, source + start, end - start);
    value[end - start] = '\0';
    return value;
}

uint32_t tokensToNodes(jsmntok_t* tokens, uint32_t tokensCount, JsonNode* node, const char* source) {
    uint8_t multiplier = 2;
    if (node->type == JsonNodeType::Array) {
        multiplier = 1;
    }
    for (uint32_t i = 0; i < tokensCount; i += multiplier) {
        jsmntok_t key;
        jsmntok_t value;
        if (node->type == JsonNodeType::Array) {
            key = tokens[i];
            value = tokens[i];
        } else {
            key  = tokens[i];
            value = tokens[i + 1];
        }

        if (value.type == JSMN_STRING) {
            if (node->type == JsonNodeType::Array) {
                JsonNode* child = getEmptyJsonNode("",JsonNodeType::String);

                char* valueString = getSubstr(source, value.start, value.end);
                addValueString(child, valueString);
                free(valueString);
                addChild(node, child);

                continue;
            }
            char* keyValue = getSubstr(source, key.start, key.end);
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeType::String);
            free(keyValue);

            char* valueString = getSubstr(source, value.start, value.end);
            addValueString(child, valueString);
            free(valueString);
            addChild(node, child);
            continue;
        }

        if (value.type == JSMN_PRIMITIVE) {
            if (node->type == JsonNodeType::Array) {
                JsonNode* child = getEmptyJsonNode("",JsonNodeType::String);
                char* valueString = getSubstr(source, value.start, value.end);
                addChild(node, child);

                if (valueString[0] == 'n') {
                    child->type = JsonNodeType::Null;
                    child->value.s = nullptr;
                } else if (valueString[0] == 't') {
                    child->type = JsonNodeType::Bool;
                    child->value.b = 1;
                } else if (valueString[0] == 'f') {
                    child->type = JsonNodeType::Bool;
                    child->value.b = 0;
                } else {
                    char* stopString = nullptr;
                    if (strstr(valueString, ".")) {
                        child->type = JsonNodeType::Float;
                        child->value.f = strtof(valueString, &stopString);
                    } else {
                        child->type = JsonNodeType::Int;
                        child->value.i = (int) strtol(valueString, &stopString, 10);
                    }
                }
                free(valueString);
                continue;
            }

            char* keyValue = getSubstr(source, key.start, key.end);
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeType::Object);
            free(keyValue);
            addChild(node, child);

            char* valueString = getSubstr(source, value.start, value.end);
            if (valueString[0] == 'n') {
                child->type = JsonNodeType::Null;
                child->value.s = nullptr;
            } else if (valueString[0] == 't') {
                child->type = JsonNodeType::Bool;
                child->value.b = 1;
            } else if (valueString[0] == 'f') {
                child->type = JsonNodeType::Bool;
                child->value.b = 0;
            } else {
                char* stopString;
                if (strstr(valueString, ".")) {
                    child->type = JsonNodeType::Float;
                    child->value.f = strtof(valueString, &stopString);
                } else {
                    child->type = JsonNodeType::Int;
                    child->value.i = (int) strtol(valueString, &stopString, 10);
                }
            }
            free(valueString);
            continue;
        }

        if (value.type == JSMN_OBJECT) {
            JsonNode* child;
            if (node->type ==  JsonNodeType::Array) {
                child = getEmptyJsonNode("",JsonNodeType::Object);
            } else {
                char* keyValue = getSubstr(source, key.start, key.end);
                child = getEmptyJsonNode(keyValue,JsonNodeType::Object);
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
            JsonNode* child = getEmptyJsonNode(keyValue,JsonNodeType::Array);
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

JsonNode* Ant::jsonNodeParse(const char *source) {
    JsonNode* node = nullptr;

    jsmn_parser parser;
    uint8_t multiplier = 1;
    uint16_t baseCount = 512;

    while (true) {
        jsmntok_t tokensParsed[baseCount * multiplier];
        jsmn_init(&parser);
        int parsedCount = jsmn_parse(
                &parser,
                source,
                strlen(source),
                tokensParsed,
                baseCount * multiplier
        );

        // If there was error return nullptr
        if (parsedCount == JSMN_ERROR_INVAL || parsedCount == JSMN_ERROR_PART) {
            return nullptr;
        }

        if (parsedCount == JSMN_ERROR_NOMEM) {
            multiplier++;
            continue;
        }
        node = getEmptyJsonNode("", JsonNodeType::Object);

        jsmntok_t tokensWithoutRootObject[parsedCount - 1];
        memcpy(tokensWithoutRootObject, tokensParsed + 1, (parsedCount - 1) * sizeof(jsmntok_t));

        tokensToNodes(tokensWithoutRootObject, parsedCount - 1, node, source);
        return node;
    }

}