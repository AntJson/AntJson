#include "json.h"
#include <string.h>
#include <stdlib.h>

void reallocateJsonNodeChildren(JsonNode* node, uint32_t size) {
    if (size == 0) {
        return;
    }
    if (node->children == NULL) {
        node->children = (JsonNode**) calloc(size, sizeof(JsonNode*));
    } else {
        JsonNode** newArray = (JsonNode**) calloc(size, sizeof(JsonNode*));
        memcpy(newArray, node->children, (size - 1) * sizeof(JsonNode*));
        node->children = newArray;
    }
}

int addChild(JsonNode* node, JsonNode* child) {
    if (node->type != JsonNodeTypeObject && node->type != JsonNodeTypeArray) {
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
        case JsonNodeTypeObject:
            node->children = (JsonNode**) value;
            break;
        case JsonNodeTypeInt:
            node->value.i = (*(int*) value);
            break;
        case JsonNodeTypeFloat:
            node->value.f = (*(float*) value);
            break;
        case JsonNodeTypeString:
            node->value.s = (char*) value;
            break;
    }
}

uint8_t getChildType(JsonNode* node) {
    if (node->arrayElementsType != JsonNodeTypeObject) {
        return node->arrayElementsType;
    }
    if (node->childrenLength <= 0) {
        return -1;
    }
    uint8_t prev = node->children[0]->type;
    for (uint32_t i = 1; i < node->childrenLength; i++) {
        if (prev != node->children[i]->type) {
            return -1;
        }
        prev = node->children[i]->type;
    }
    return prev;
}

int isChildrenEqual(JsonNode* a, JsonNode* b) {
    if (a->type == JsonNodeTypeArray) {
        uint8_t aChildType = getChildType(a);
        uint8_t bChildType = getChildType(b);
        if (aChildType == bChildType && aChildType >= 0) {
            return 1;
        }
        return 0;
    }
    if (a->childrenLength != b->childrenLength) {
        return 0;
    }
    for (int i = 0; i < a->childrenLength; i++) {
        int found = 0;
        for (int j = 0; j < b->childrenLength; j++) {
            if (!strcmp(a->children[i]->key, b->children[j]->key)) {
                found = 1;
                if (!jsonIsEqualScheme(a->children[i], b->children[j])) {
                    return 0;
                }
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

int jsonIsEqualScheme(JsonNode* a, JsonNode* b) {
    if (a->type == b->type && strcmp(a->key, b->key) == 0) {
        if (a->type == JsonNodeTypeObject || a->type == JsonNodeTypeArray) {
            return isChildrenEqual(a, b);
        }
        return 1;
    }
    return 0;
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
    if (node == NULL) {
        return;
    }
    if ((node->type == JsonNodeTypeObject || node->type == JsonNodeTypeArray) && node->childrenLength != 0 && node->children != NULL) {
        for (int i = 0; i < node->childrenLength; i++) {
            disposeJsonNode(node->children[i]);
        }
    }
    if (node->children != NULL) {
        free(node->children);
    }
    free(node);
}