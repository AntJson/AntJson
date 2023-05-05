#include <stdint.h>
#ifndef __JSON_HEADER__
#define __JSON_HEADER__

typedef enum JsonNodeType_t {
    object = 0,
    number_i = 1,
    number_f = 2,
    string = 3,
} JsonNodeType;

typedef union JsonValue_t{
    int i;
    float f;
    char* s;
    // bool b;
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
    // Count of childrens
    uint8_t childrenLength;
} JsonNode;

int addChild(JsonNode* node, JsonNode* child);
void updateNode(JsonNode* node, JsonNodeType type, char* key, void* value);
double arrayLength(JsonNode** array);
int jsonIsEqualScheme(JsonNode* a, JsonNode* b);

#endif // __JSON_HEADER__