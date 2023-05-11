#ifndef JSON_H
#define JSON_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus

#define JsonNodeTypeObject JsonNodeType::Object
#define JsonNodeTypeInt JsonNodeType::Int
#define JsonNodeTypeFloat JsonNodeType::Float
#define JsonNodeTypeString JsonNodeType::String
#define JsonNodeTypeBool JsonNodeType::Bool
#define JsonNodeTypeNull JsonNodeType::Null

typedef enum class
JsonNodeType {
    Object  = 0,
    Int     = 1,
    Float   = 2,
    String  = 3,
    Bool    = 4,
    Null    = 5,
};
#else
typedef enum
JsonNodeType_t {
    JsonNodeTypeObject  = 0,
    JsonNodeTypeInt     = 1,
    JsonNodeTypeFloat   = 2,
    JsonNodeTypeString  = 3,
    JsonNodeTypeBool    = 4,
    JsonNodeTypeNull    = 5,
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
int jsonIsEqualScheme(JsonNode *a, JsonNode *b);


#ifdef __cplusplus
}
#endif

#endif // JSON_H