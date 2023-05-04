#ifndef __JSON_HEADER__
#define __JSON_HEADER__

typedef enum {
    object = 0,
    array = 1,
    number_i = 2,
    number_f = 3,
    string = 4,
} JsonNodeType;

typedef union
{
    int i;
    double f;
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
    JsonValue* value;
    // Not null if type is object
    struct JsonNode_t* data;
    // Not null if type is array
    struct JsonNode_t** children;
} JsonNode;

void jsonAddField(JsonNode* node, JsonNodeType type, char* key, void* value);
double arrayLength(JsonNode** array);
int jsonIsEqualScheme(JsonNode* a, JsonNode* b);

#endif // __JSON_HEADER__