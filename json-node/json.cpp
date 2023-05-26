#include "json.h"
#include <cstring>
#include <cstdlib>

using namespace Ant;

void reallocateJsonNodeChildren(JsonNode* node, uint32_t size) {
    if (size == 0) {
        return;
    }
    if (node->children == nullptr) {
        node->children = (JsonNode**) calloc(size, sizeof(JsonNode*));
    } else {
        auto** newArray = (JsonNode**) calloc(size, sizeof(JsonNode*));
        for (int i = 0; i < node->childrenLength; i++) {
            newArray[i] = node->children[i];
        }
        free(node->children);
        node->children = newArray;
    }
}

int Ant::addChild(JsonNode* node, JsonNode* child) {
    if (node->type != JsonNodeType::Object && node->type != JsonNodeType::Array) {
        return -1;
    }
    reallocateJsonNodeChildren(node, node->childrenLength + 1);
    node->children[node->childrenLength++] = child;
    return 0;
}

JsonNodeType getChildType(JsonNode* node) {
    if (node->arrayElementsType != JsonNodeType::Undefined || node->childrenLength == 0) {
        return node->arrayElementsType;
    }
    if (node->childrenLength < 0) {
        return JsonNodeType::Undefined;
    }
    JsonNodeType prev = node->children[0]->type;
    for (uint32_t i = 1; i < node->childrenLength; i++) {
        if (prev != node->children[i]->type) {
            return JsonNodeType::Undefined;
        }
        prev = node->children[i]->type;
    }
    return prev;
}

int isChildrenEqual(JsonNode* reference, JsonNode* schema) {
    if (reference->type == JsonNodeType::Array) {
        JsonNodeType aChildType = getChildType(reference);
        JsonNodeType bChildType = getChildType(schema);
        if (aChildType == bChildType && aChildType != JsonNodeType::Undefined) {
            if (aChildType != JsonNodeType::Object) {
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

int Ant::jsonIsEqualScheme(JsonNode *reference, JsonNode *schema) {

    if (reference == nullptr || schema == nullptr) {
        return 0;
    }
    if (reference->type == schema->type && strcmp(reference->key, schema->key) == 0) {
        if (reference->type == JsonNodeType::Object || reference->type == JsonNodeType::Array) {
            return isChildrenEqual(reference, schema);
        }
        return 1;
    }
    return 0;
}

void Ant::addKey(JsonNode* node, const char* key) {
    if (strlen(key) == 0) {
        node->key = "";
        return;
    }
    node->key = (char*)malloc(sizeof(char) * strlen(key) + 1);
    strcpy(node->key, key);
    node->key[strlen(key)] = '\0';
}

int Ant::addValueString(JsonNode* node, const char* value) {
    node->value.s = (char*)malloc(sizeof(char) * strlen(value) + 1);
    strcpy(node->value.s, value);
    node->value.s[strlen(value)] = '\0';
    return 0;
}

JsonNode* Ant::getEmptyJsonNode(const char* key, JsonNodeType type) {
    auto* node = (JsonNode*)malloc(sizeof (JsonNode));
    node->key = nullptr;
    node->value.s = nullptr;
    node->children = nullptr;

    Ant::addKey(node, key);
    node->type = type;
    node->childrenLength = 0;
    node->arrayElementsType = JsonNodeType::Undefined;
    return node;
}

void Ant::disposeJsonNode(JsonNode* node) {
    if (node == nullptr) {
        return;
    }
    if ((node->type == JsonNodeType::Object || node->type == JsonNodeType::Array) && node->childrenLength != 0 && node->children != nullptr) {
        for (int i = 0; i < node->childrenLength; i++) {
            Ant::disposeJsonNode(node->children[i]);
        }
    }
    if (node->key != nullptr && strlen(node->key) != 0) {
        free(node->key);
    }
    if (node->children != nullptr) {
        free(node->children);
    }
    if (node->type == JsonNodeType::String && node->value.s != nullptr) {
        free(node->value.s);
    }
    free(node);
}