#ifndef JSON_H
#define JSON_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
    namespace Ant {
#endif


#ifdef __cplusplus

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

enum class UnpackFlag {
    FromJson    = 0,
    ToJson      = 1,
};
#else
typedef enum
JsonNodeType_t {
    JsonNodeTypeUndefined   = 0,
    JsonNodeTypeObject      = 1,
    JsonNodeTypeInt         = 2,
    JsonNodeTypeFloat       = 3,
    JsonNodeTypeString      = 4,
    JsonNodeTypeBool        = 5,
    JsonNodeTypeNull        = 6,
    JsonNodeTypeArray       = 7,
} JsonNodeType;
#endif

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
    // Not null if type is [number | string | bool]
    JsonValue value;
    // Not null if type is object
    struct JsonNode_t **children;
    // Count of children
    uint32_t childrenLength;
} JsonNode;

// JsonNode function helpers
JsonNode *getEmptyJsonNode(const char *key, JsonNodeType type);

// Free all allocated memory for all node tree
void disposeJsonNode(JsonNode *node);

// Add child to parent node with setting child->parent also
int addChild(JsonNode *node, JsonNode *child);


void addKey(JsonNode* node, const char* key);
int addValueString(JsonNode* node, const char* value);

// Checks if two JsonNodes has the same scheme
int jsonIsEqualScheme(JsonNode *reference, JsonNode *schema);


#ifdef __cplusplus
};};
#endif

#endif // JSON_H