#include "json.h"
#include <stdio.h>
#include <string.h>

void jsonAddField(JsonNode* node, JsonNodeType type, char* key, void* value) {
    JsonValue* jValue;
    node->type = type;
    node->key = key;
    switch (type)
    {
        case object:
            node->data = (JsonNode*) value;
            break;
        case array:
            node->data = (JsonNode**) value;
            break;
        case number_i:
            jValue = (JsonValue*)malloc(sizeof(JsonValue));
            jValue->i = (*(int*) value);
            node->value = jValue;
            break;
        case number_f:
            jValue = (JsonValue*)malloc(sizeof(JsonValue));
            jValue->f = (*(double*) value);
            node->value = jValue;
            break;
        case string:
            jValue = (JsonValue*)malloc(sizeof(JsonValue));
            jValue->s = (*(char*) value);
            node->value = jValue;
            break;
    }
}

int jsonIsEqualScheme(JsonNode* a, JsonNode* b) {
    printf("[A] | key: %s | type: %d\n", a->key, a->type);
    printf("[B] | key: %s | type: %d\n", b->key, b->type);
    if (a->type == b->type && strcmp(a->key, b->key) == 0) {
        if (a->type == object) {
            return jsonIsEqualScheme((*a).data, (*b).data);
        }
        if (a->type == array) {
            if (arrayLength(a->children) != arrayLength(b->children)) {
                return 0;
            }
            int isEquals = 1;
            for (int i = 0; i < arrayLength(a->children); i++) {
                isEquals = isEquals && jsonIsEqualScheme(a->children[i], b->children[i]);
            }
            return isEquals;
        }
        return 1;
    }
    return 0;
}

double arrayLength(JsonNode** array) {
    return sizeof(array) / sizeof(*array);
}