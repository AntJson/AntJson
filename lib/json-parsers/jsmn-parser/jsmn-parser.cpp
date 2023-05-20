#include "jsmn-parser.h"

int Ant::JsmnParser::tokensToNodes(jsmntok_t* tokens, uint32_t tokensCount, Ant::JsonNode* node, const char* source) {
    uint8_t multiplier = 2;
    if (node->type == Ant::JsonNodeType::Array) {
        multiplier = 1;
    }
    for (uint32_t i = 0; i < tokensCount; i += multiplier) {
        jsmntok_t key;
        jsmntok_t value;
        if (node->type == Ant::JsonNodeType::Array) {
            key = tokens[i];
            value = tokens[i];
        } else {
            key  = tokens[i];
            value = tokens[i + 1];
        }

        if (value.type == JSMN_STRING) {
            if (node->type == Ant::JsonNodeType::Array) {
                Ant::JsonNode* child = getEmptyJsonNode("",Ant::JsonNodeType::String);

                char* valueString = (char*)malloc(sizeof (char) * (value.end - value.start));
                valueString = strncpy(valueString, source + value.start, value.end - value.start);
                child->value.s = valueString;
                addChild(node, child);

                continue;
            }
            char* keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
            strncpy(keyValue, source + key.start, key.end - key.start);
            Ant::JsonNode* child = getEmptyJsonNode(keyValue,Ant::JsonNodeType::String);

            char* valueString = (char*)malloc(sizeof (char) * (value.end - value.start));
            valueString = strncpy(valueString, source + value.start, value.end - value.start);
            child->value.s = valueString;
            addChild(node, child);
            continue;
        }

        if (value.type == JSMN_PRIMITIVE) {
            if (node->type == Ant::JsonNodeType::Array) {
                Ant::JsonNode* child = getEmptyJsonNode("",Ant::JsonNodeType::String);

                char* valueString = (char*)malloc(sizeof (char) * (value.end - value.start));
                valueString = strncpy(valueString, source + value.start, value.end - value.start);
                addChild(node, child);

                if (valueString[0] == 'n') {
                    child->type = Ant::JsonNodeType::Null;
                    child->value.s = NULL;
                } else if (valueString[0] == 't') {
                    child->type = Ant::JsonNodeType::Bool;
                    child->value.b = 1;
                } else if (valueString[0] == 'f') {
                    child->type = Ant::JsonNodeType::Bool;
                    child->value.b = 0;
                } else {
                    char* stopString;
                    if (strstr(valueString, ".")) {
                        child->type = Ant::JsonNodeType::Float;
                        child->value.f = strtof(valueString, &stopString);
                    } else {
                        child->type = Ant::JsonNodeType::Int;
                        child->value.i = (int) strtol(valueString, &stopString, 10);
                    }
                }

                continue;
            }

            char* keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
            strncpy(keyValue, source + key.start, key.end - key.start);
            Ant::JsonNode* child = getEmptyJsonNode(keyValue,Ant::JsonNodeType::Object);
            addChild(node, child);

            char* valueString = (char*)malloc(sizeof(char) * (value.end - value.start));
            valueString = strncpy(valueString, source + value.start, value.end - value.start);
            if (valueString[0] == 'n') {
                child->type = Ant::JsonNodeType::Null;
                child->value.s = NULL;
            } else if (valueString[0] == 't') {
                child->type = Ant::JsonNodeType::Bool;
                child->value.b = 1;
            } else if (valueString[0] == 'f') {
                child->type = Ant::JsonNodeType::Bool;
                child->value.b = 0;
            } else {
                char* stopString;
                if (strstr(valueString, ".")) {
                    child->type = Ant::JsonNodeType::Float;
                    child->value.f = strtof(valueString, &stopString);
                } else {
                    child->type = Ant::JsonNodeType::Int;
                    child->value.i = (int) strtol(valueString, &stopString, 10);
                }
            }
            continue;
        }

        if (value.type == JSMN_OBJECT) {
            char* keyValue;
            if (node->type ==  Ant::JsonNodeType::Array) {
                keyValue = "";
            } else {
                keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
                strncpy(keyValue, source + key.start, key.end - key.start);
            }
            Ant::JsonNode* child = getEmptyJsonNode(keyValue,Ant::JsonNodeType::Object);
            addChild(node, child);

            jsmntok_t objectTokens[value.size * 2];
            memcpy(objectTokens, tokens + i + multiplier, (value.size * 2) * sizeof(*tokens));
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

            char* keyValue = (char*) malloc(sizeof(char) * (key.end - key.start));
            strncpy(keyValue, source + key.start, key.end - key.start);
            Ant::JsonNode* child = getEmptyJsonNode(keyValue,Ant::JsonNodeType::Array);
            addChild(node, child);

            jsmntok_t objectTokens[arrayNodesCount];
            memcpy(objectTokens, tokens + i + 2, (arrayNodesCount) * sizeof(*tokens));
            tokensToNodes(objectTokens, arrayNodesCount, child, source);
            i += (arrayNodesCount);

            continue;
        }
    }
    return tokensCount;
}

int Ant::JsmnParser::parseTokens() {
    parsedTokens = new jsmntok_t[128];
    jsmn_init(&parser);

    parsedTokensCount = jsmn_parse(
            &parser,
            sourceJson.c_str(),
            strlen(sourceJson.c_str()),
            parsedTokens,
            128);

    if (parsedTokensCount <= 0) {
        return 0;
    }

    jsmntok_t tokensWoutRootObject[parsedTokensCount - 1];
    memcpy(tokensWoutRootObject, parsedTokens + 1, (parsedTokensCount - 1) * sizeof(jsmntok_t));

    delete parsedTokens;
    parsedTokensCount--;
    parsedTokens = new jsmntok_t[parsedTokensCount];
    memcpy(parsedTokens, tokensWoutRootObject, parsedTokensCount * sizeof(jsmntok_t));

    return parsedTokensCount;
}

Ant::JsonNode *Ant::JsmnParser::parse() {
    parseTokens();
    tokensToNodes(parsedTokens, parsedTokensCount, rootNode, sourceJson.c_str());

    return rootNode;
}