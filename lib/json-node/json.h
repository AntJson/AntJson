#ifndef JSON_H
#define JSON_H

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <cstdio>

namespace Ant {

enum class JsonNodeType {
    Undefined   = 0,
    Object      = 1,
    Int         = 2,
    Float       = 3,
    String      = 4,
    Bool        = 5,
    Null        = 6,
    Array       = 7,
};


typedef union JsonValue_t {
    int     i;
    float   f;
    char*   s;
    int     b;
} JsonValue;


typedef struct JsonNode_t {
    // Json type of field related to current key
    JsonNodeType type;
    // Type of array elements
    JsonNodeType arrayElementsType;
    // Key in json map
    char *key;
    // Pointer to parent node
    struct JsonNode_t *parent;
    // Not null if type is [number | string | bool]
    JsonValue value;
    // Not null if type is object
    struct JsonNode_t **children;
    // Count of children
    uint32_t childrenLength;
} JsonNode;

// JsonNode function helpers
JsonNode *getEmptyJsonNode(char *key, JsonNodeType type);

// Free all allocated memory for all node tree
void disposeJsonNode(JsonNode *node);

// Add child to parent node with setting child->parent also
int addChild(JsonNode *node, JsonNode *child);

// Checks if two JsonNodes has the same scheme
int jsonIsEqualScheme(JsonNode *reference, JsonNode *schema);


};

#endif // JSON_H