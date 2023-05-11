#include "../json-node/json.h"
#include <string.h>
#include <stdlib.h>


#ifndef DTOFromJsonName
#define DTOFromJsonName(structName) structName##FromJson
#endif // DTOFromJsonName

#ifndef DTOChildrenUnpackName
#define DTOChildrenUnpackName(structName) __children__unpack__##structName
#endif // DTOChildrenUnpackName

#ifndef DTOToJsonSchemeName
#define DTOToJsonSchemeName(structName) structName##ToJsonScheme
#endif // DTOToJsonSchemeName

#ifndef DTOStructConstructor
#define DTOStructConstructor(jsonKey, fieldName, type)                                  \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        DTOFromJsonName(type)(source, dest->fieldName);                                 \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        DTOFromJsonName(type)(source->children[i], dest->fieldName);                    \
    }                                                                                   \
    if (flag == 2) {                                                                    \
        JsonNode* child = DTOToJsonSchemeName(type)();                                  \
        child->key = jsonKey;                                                           \
        addChild(parent, child);                                                        \
    }
#endif // DTOStructConstructor

#ifndef DTOFieldConstructor
#define DTOFieldConstructor(jsonKey, fieldName, unionType, nodeType)                    \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        dest->fieldName = source->value.unionType;                                      \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        dest->fieldName = source->children[i]->value.unionType;                         \
    }                                                                                   \
    if (flag == 2) {                                                                    \
        JsonNode* child = getEmptyJsonNode(jsonKey, nodeType);                          \
        addChild(parent, child);                                                        \
    }
#endif // DTOFieldConstructor

#ifndef DTOConstructor
#define DTOConstructor(structType, ...)                                                 \
    DTOChildrenUnpack(structType, ##__VA_ARGS__)                                        \
    int DTOFromJsonName(structType)(JsonNode* source, structType* dest) {               \
        if (source->type == object) {                                                   \
            DTOChildrenUnpackName(structType)(source, dest);                            \
        }                                                                               \
        const int flag = 0;                                                             \
        const int i = 0;                                                                \
        JsonNode* parent = NULL;                                                        \
        __VA_ARGS__                                                                     \
        return 0;                                                                       \
    }                                                                                   \
    JsonNode* DTOToJsonSchemeName(structType) () {                                      \
        const int flag = 2;                                                             \
        JsonNode* source = NULL;                                                        \
        structType* dest = NULL;                                                        \
        const int i = 0;                                                                \
        JsonNode* parent = getEmptyJsonNode("", object);                                \
        __VA_ARGS__                                                                     \
        return parent;                                                                  \
    }                                                                                   \

#endif // DTOConstructor

#ifndef DTOChildrenUnpack
#define DTOChildrenUnpack(structType, ...)                                              \
    int DTOChildrenUnpackName(structType)(JsonNode* source, structType* dest) {         \
        const int flag = 1;                                                             \
        JsonNode* parent = NULL;                                                        \
        if (source->type != object) {                                                   \
            return -1;                                                                  \
        }                                                                               \
        for (int i = 0; i < source->childrenLength; i++) {                              \
            __VA_ARGS__                                                                 \
        }                                                                               \
        return 0;                                                                       \
    }
#endif // DTOChildrenUnpack