#include "json.h"
#include <cstring>
#include <cstdlib>

void reallocateJsonNodeChildren(Ant::JsonNode* node, uint32_t size) {
    if (size == 0) {
        return;
    }
    if (node->children == nullptr) {
        node->children = (Ant::JsonNode**) calloc(size, sizeof(Ant::JsonNode*));
    } else {
        auto** newArray = (Ant::JsonNode**) calloc(size, sizeof(Ant::JsonNode*));
        memcpy(newArray, node->children, (size - 1) * sizeof(Ant::JsonNode*));
        node->children = newArray;
    }
}

int Ant::addChild(Ant::JsonNode* node, Ant::JsonNode* child) {
    if (node->type != Ant::JsonNodeType::Object && node->type != Ant::JsonNodeType::Array) {
        return -1;
    }
    child->parent = node;
    reallocateJsonNodeChildren(node, node->childrenLength + 1);
    node->children[node->childrenLength++] = child;
    return 0;
}

void updateNode(Ant::JsonNode* node, Ant::JsonNodeType type, char* key, void* value) {
    Ant::JsonValue* jValue;
    node->type = type;
    node->key = key;
    switch (type)
    {
        case Ant::JsonNodeType::Object:
            node->children = (Ant::JsonNode**) value;
            break;
        case Ant::JsonNodeType::Int:
            node->value.i = (*(int*) value);
            break;
        case Ant::JsonNodeType::Float:
            node->value.f = (*(float*) value);
            break;
        case Ant::JsonNodeType::String:
            node->value.s = (char*) value;
            break;
    }
}

uint8_t getChildType(Ant::JsonNode* node) {
    if (node->arrayElementsType != Ant::JsonNodeType::Undefined || node->childrenLength == 0) {
        return static_cast<uint8_t>(node->arrayElementsType);
    }
    if (node->childrenLength < 0) {
        return -1;
    }
    auto prev = static_cast<uint8_t>(node->children[0]->type);
    for (uint32_t i = 1; i < node->childrenLength; i++) {
        if (static_cast<Ant::JsonNodeType>(prev) != node->children[i]->type) {
            return -1;
        }
        prev = static_cast<uint8_t>(node->children[i]->type);
    }
    return prev;
}

int isChildrenEqual(Ant::JsonNode* reference, Ant::JsonNode* schema) {
    if (reference->type == Ant::JsonNodeType::Array) {
        uint8_t aChildType = getChildType(reference);
        uint8_t bChildType = getChildType(schema);
        if (aChildType == bChildType && aChildType >= 0) {
            if (static_cast<Ant::JsonNodeType>(aChildType) != Ant::JsonNodeType::Object) {
                return 1;
            }
            if (reference->childrenLength == 0 && schema->childrenLength == 0) {
                return 1;
            }
            if (reference->childrenLength > 0 && schema->childrenLength > 0) {
                int result = 1;
                for (uint32_t j = 0; j < schema->childrenLength; j++) {
                    result = result && jsonIsEqualScheme(reference->children[0], schema->children[j]);
                }
                return result;
            }
            return 0;
        }
        return 0;
    }
    if (reference->childrenLength != schema->childrenLength) {
        return 0;
    }
    for (int i = 0; i < reference->childrenLength; i++) {
        int found = 0;
        for (int j = 0; j < schema->childrenLength; j++) {
            if (!strcmp(reference->children[i]->key, schema->children[j]->key)) {
                found = 1;
                if (!jsonIsEqualScheme(reference->children[i], schema->children[j])) {
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

int Ant::jsonIsEqualScheme(Ant::JsonNode *reference, Ant::JsonNode *schema) {

    if (reference == nullptr || schema == nullptr) {
        return 0;
    }
    if (reference->type == schema->type && strcmp(reference->key, schema->key) == 0) {
        if (reference->type == Ant::JsonNodeType::Object || reference->type == Ant::JsonNodeType::Array) {
            return isChildrenEqual(reference, schema);
        }
        return 1;
    }
    return 0;
}

Ant::JsonNode* Ant::getEmptyJsonNode(char* key, Ant::JsonNodeType type) {
    auto* node = (Ant::JsonNode*)malloc(sizeof (Ant::JsonNode));
    node->key = key;
    node->type = type;
    node->childrenLength = 0;
    reallocateJsonNodeChildren(node, 0);
    return node;
}

void Ant::disposeJsonNode(Ant::JsonNode* node) {
    if (node == nullptr) {
        return;
    }
    if ((node->type == Ant::JsonNodeType::Object || node->type == Ant::JsonNodeType::Array) && node->childrenLength != 0 && node->children != NULL) {
        for (int i = 0; i < node->childrenLength; i++) {
            Ant::disposeJsonNode(node->children[i]);
        }
    }
    if (node->children != NULL) {
        free(node->children);
    }
    free(node);
}