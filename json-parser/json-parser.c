//
// Created by danysmall on 5/11/23.
//
// NOTE: the token-to-node walk was rewritten to recurse over the real DFS token
// span rather than copying a fixed value.size * 2 slice. The original walk
// miscounted nested objects/arrays (jsmn's size counts only direct children, so
// descendants were dropped and read out of place), which left nested objects
// empty and leaked their members as siblings. The recursive form consumes
// 1 token for the value plus its real subtree, so nesting is preserved exactly.
//
#include "../json-node/json.h"
#include <jsmn.h>

char* getSubstr(const char* source, int start, int end) {
    char* value = (char*)malloc(sizeof(char) * (end - start) + 1);
    strncpy(value, source + start, end - start);
    value[end - start] = '\0';
    return value;
}

// Parses the value token at tokens[cursor], building a node with the supplied key
// (an empty key for array elements / the root) and returning it through *out.
// Returns the number of tokens consumed by this value (itself plus all of its
// descendants), so callers advance the cursor by exactly the subtree span.
// The caller owns the returned node (its parent adds it via addChild, or
// jsonNodeParse returns it directly as the root).
static uint32_t parseValue(const jsmntok_t* tokens, uint32_t cursor, const char* key,
                           const char* source, JsonNode** out) {
    const jsmntok_t tok = tokens[cursor];
    *out = NULL;

    if (tok.type == JSMN_STRING) {
        JsonNode* child = getEmptyJsonNode(key, JsonNodeTypeString);
        char* valueString = getSubstr(source, tok.start, tok.end);
        addValueString(child, valueString);
        free(valueString);
        *out = child;
        return 1;
    }

    if (tok.type == JSMN_PRIMITIVE) {
        JsonNode* child = getEmptyJsonNode(key, JsonNodeTypeObject);
        char* valueString = getSubstr(source, tok.start, tok.end);
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
        *out = child;
        return 1;
    }

    if (tok.type == JSMN_OBJECT) {
        JsonNode* child = getEmptyJsonNode(key, JsonNodeTypeObject);
        uint32_t idx = cursor + 1;
        for (int p = 0; p < tok.size; ++p) {
            const jsmntok_t keyTok = tokens[idx];
            char* keyStr = getSubstr(source, keyTok.start, keyTok.end);
            idx += 1;
            JsonNode* member = NULL;
            uint32_t consumed = parseValue(tokens, idx, keyStr, source, &member);
            idx += consumed;
            free(keyStr);
            if (member != NULL) {
                addChild(child, member);
            }
        }
        *out = child;
        return idx - cursor;
    }

    if (tok.type == JSMN_ARRAY) {
        JsonNode* child = getEmptyJsonNode(key, JsonNodeTypeArray);
        uint32_t idx = cursor + 1;
        for (int e = 0; e < tok.size; ++e) {
            JsonNode* element = NULL;
            uint32_t consumed = parseValue(tokens, idx, "", source, &element);
            idx += consumed;
            if (element != NULL) {
                addChild(child, element);
            }
        }
        *out = child;
        return idx - cursor;
    }

    // Unknown token kind: skip it without producing a node.
    return 1;
}

JsonNode* jsonNodeParse(const char* source) {
    jsmn_parser parser;
    uint8_t multiplier = 1;
    uint16_t baseCount = 512;

    while (1) {
        jsmntok_t tokensParsed[baseCount * multiplier];
        jsmn_init(&parser);
        int parsedCount = jsmn_parse(
                &parser,
                source,
                strlen(source),
                tokensParsed,
                baseCount * multiplier
        );

        // If there was an error return NULL.
        if (parsedCount == JSMN_ERROR_INVAL || parsedCount == JSMN_ERROR_PART) {
            return NULL;
        }
        if (parsedCount == JSMN_ERROR_NOMEM) {
            multiplier++;
            continue;
        }
        // A valid document yields at least one token (the root). Guard an
        // unexpected zero count so an empty or degenerate body returns NULL
        // instead of reading tokensParsed out of bounds.
        if (parsedCount < 1) {
            return NULL;
        }

        JsonNode* root = NULL;
        parseValue(tokensParsed, 0, "", source, &root);
        return root;
    }
}