//
// Created by danysmall on 5/11/23.
//

#include "node-converter.h"
#include <string.h>

JsonNode* jsonTokenToJsonNode(JsonToken* token, JsonNode* node) {
    if (token == NULL) {
        return NULL;
    }
    //  if children NULL means this is value token
    //  if not means this object/key token
    if (token->children == NULL) {
        if (token->data != NULL) {
            node->type = string;
            node->value.s = token->data;
        }
        if (node->parent != NULL) {
            node = node->parent;
        }
    } else {
        for (uint32_t i = 0; i < token->childrenLength; i++) {
            JsonNode* childNode;
            if (token->key != NULL) {
                childNode = getEmptyJsonNode(token->key, object);
            } else {
                childNode = getEmptyJsonNode("", object);
            }
            addChild(node, childNode);
            node = childNode;
            jsonTokenToJsonNode(token->children[i], node);
        }
    }
//    if (token->data != NULL && !strcmp(token->data, "")) {
//        if (token->data[0] == '"') {
//            node->type = string;
//            node->value.s = token->data;
//        }
//    }
//    if (token->children != NULL && token->childrenLength != 0) {
//        for (uint32_t i = 0; i < token->childrenLength; i++) {
////            If token is key
//            if (token->children[i]->key != NULL) {
//                JsonNode* childNode = getEmptyJsonNode(token->children[i]->key, string);
//                addChild(node, childNode);
//                node = childNode;
//            }
////            If token is value of previous key
//            if (token->parent != NULL && token->parent->key != NULL) {
//                if (token->data != NULL) {
//                    node->value.s = token->data;
//                }
//                node = node->parent;
//            }
//        }
//    }
}