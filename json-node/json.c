#include "json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int addChild(JsonNode* node, JsonNode* child) {
    if (node->type != object) {
        return -1;
    }
    child->parent = node;
    reallocateJsonNodeChildren(node, node->childrenLength + 1);
    node->children[node->childrenLength++] = child;
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
            node->value.s = (char*) value;
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

JsonNode* getEmptyJsonNode(char* key, JsonNodeType type) {
    JsonNode* node = (JsonNode*)malloc(sizeof (JsonNode));
    node->key = key;
    node->type = type;
    node->childrenLength = 0;
    reallocateJsonNodeChildren(node, 0);
    return node;
}

void disposeJsonNode(JsonNode* node) {
    if (node->type == object && node->childrenLength != 0 && node->children != NULL) {
        for (int i = 0; i < node->childrenLength; i++) {
            disposeJsonNode(node->children[0]);
        }
    }
    if (node->children != NULL) {
        free(node->children);
    }
    if (node != NULL) {
        free(node);
    }
}

void reallocateJsonNodeChildren(JsonNode* node, uint32_t size) {
    if (size == 0) {
        return;
    }
    if (node->children == NULL) {
        node->children = (JsonNode**) calloc(size, sizeof(JsonNode*));
    } else {
        realloc(node->children, sizeof (JsonNode*) * size);
    }
}