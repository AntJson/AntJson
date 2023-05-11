#include "../json-node/json.h"
#include "../json-parser/json-parser.h"

#ifdef ANT_JSON_MEMBER
    #define StaticMember static
    #define StaticPrefix(structName, constructorName) structName::constructorName
#else
    #define StaticMember
    #define StaticPrefix(structName, constructorName) constructorName
#endif

#ifdef __cplusplus
    #include <cstring>
    #include <cstdlib>
#else
    #include <string.h>
    #include <stdlib.h>
#endif // __cplusplus

#ifndef AntKeySecure
    #ifdef __cplusplus
        #define AntKeySecure(jsonKey) (char*)jsonKey
    #else
        #define AntKeySecure(jsonKey) jsonKey
    #endif // __cplusplus
#endif // AntKeySecure


#ifndef AntFromJsonName
#define AntFromJsonName(structName) structName##FromJson
#endif // AntFromJsonName

#ifndef AntChildrenUnpackName
#define AntChildrenUnpackName(structName) _children__unpack__##structName
#endif // AntChildrenUnpackName

#ifndef AntToJsonSchemeName
#define AntToJsonSchemeName(structName) structName##ToJsonScheme
#endif // AntToJsonSchemeName

#ifndef AntStruct
#define AntStruct(jsonKey, fieldName, type)                                  \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        StaticPrefix(type, AntFromJsonName(type))(source, dest->fieldName);             \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        StaticPrefix(type, AntFromJsonName(type))(source->children[i], dest->fieldName);\
    }                                                                                   \
    if (flag == 2) {                                                                    \
        JsonNode* child = StaticPrefix(type, AntToJsonSchemeName(type))();              \
        child->key = AntKeySecure(jsonKey);                                             \
        addChild(parent, child);                                                        \
    }
#endif // AntStruct

#ifndef AntValue
#define AntValue(jsonKey, fieldName, unionType, nodeType)                    \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        dest->fieldName = source->value.unionType;                                      \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        dest->fieldName = source->children[i]->value.unionType;                         \
    }                                                                                   \
    if (flag == 2) {                                                                    \
        JsonNode* child = getEmptyJsonNode(AntKeySecure(jsonKey), nodeType);            \
        addChild(parent, child);                                                        \
    }
#endif // AntValue

#ifndef AntJson
#define AntJson(structType, ...)                                                 \
    StaticMember AntChildrenUnpack(structType, ##__VA_ARGS__)\
    StaticMember int AntFromJsonName(structType)(JsonNode* source, structType* dest) {  \
        if (source->type == JsonNodeTypeObject) {                                       \
            AntChildrenUnpackName(structType)(source, dest);                            \
        }                                                                               \
        const int flag = 0;                                                             \
        const int i = 0;                                                                \
        JsonNode* parent = NULL;                                                        \
        __VA_ARGS__                                                                     \
        return 0;                                                                       \
    }                                                                                   \
    StaticMember JsonNode* AntToJsonSchemeName(structType) () {                         \
        const int flag = 2;                                                             \
        JsonNode* source = NULL;                                                        \
        structType* dest = NULL;                                                        \
        const int i = 0;                                                                \
        JsonNode* parent = getEmptyJsonNode(AntKeySecure(""), JsonNodeTypeObject);      \
        __VA_ARGS__                                                                     \
        return parent;                                                                  \
    }                                                                                   \

#endif // AntJson

#ifndef AntChildrenUnpack
#define AntChildrenUnpack(structType, ...)                                              \
    int AntChildrenUnpackName(structType)(JsonNode* source, structType* dest) {         \
        const int flag = 1;                                                             \
        JsonNode* parent = NULL;                                                        \
        if (source->type != JsonNodeTypeObject) {                                       \
            return -1;                                                                  \
        }                                                                               \
        for (int i = 0; i < source->childrenLength; i++) {                              \
            __VA_ARGS__                                                                 \
        }                                                                               \
        return 0;                                                                       \
    }
#endif // AntChildrenUnpack