#ifndef JSON_H
#define JSON_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum JsonNodeType_t {
    object = 0,
    number_i = 1,
    number_f = 2,
    string = 3,
    bool = 4,
    null = 5,
} JsonNodeType;

typedef union JsonValue_t{
    int i;
    float f;
    char* s;
    int b;
} JsonValue;


typedef struct JsonNode_t {
    // Json type of field related to current key
    JsonNodeType type;
    // Key in json map
    char* key;
    // Pointer to parent node
    struct JsonNode_t* parent;
    // Not null if type is [number | string | bool]
    JsonValue value;
    // Not null if type is object
    struct JsonNode_t** children;
    // Count of children
    uint32_t childrenLength;
} JsonNode;

// JsonNode function helpers
JsonNode* getEmptyJsonNode(char* key, JsonNodeType type);

// Free all allocated memory for all node tree
void disposeJsonNode(JsonNode* node);

// Add child to parent node with setting child->parent also
int addChild(JsonNode* node, JsonNode* child);

// Checks if two JsonNodes has the same scheme
int jsonIsEqualScheme(JsonNode* a, JsonNode* b);

#endif // JSON_H