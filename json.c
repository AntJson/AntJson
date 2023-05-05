#include "json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int addChild(JsonNode* node, JsonNode* child) {
    if (!node->type == object) {
        return -1;
    }
    child->parent = node;
    node->children[node->childrenLength] = child;
    node->childrenLength++;
}

void updateNode(JsonNode* node, JsonNodeType type, char* key, void* value) {
    JsonValue* jValue;
    node->type = type;
    node->key = key;
    switch (type)
    {
        case object:
            node->children = (JsonNode**) value;
            break;
        case number_i:
            node->value.i = (*(int*) value);
            break;
        case number_f:
            node->value.f = (*(float*) value);
            break;
        case string:
            node->value.s = (*(char*) value);
            break;
    }
}

int jsonIsEqualScheme(JsonNode* a, JsonNode* b) {
    printf("[A] | key: %s | type: %d\n", a->key, a->type);
    printf("[B] | key: %s | type: %d\n", b->key, b->type);
    if (a->type == b->type && strcmp(a->key, b->key) == 0) {
        if (a->type == object) {
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