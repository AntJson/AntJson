#include "../json-node/json.h"
#include "../json-parser/json-parser.h"

#ifdef ANT_JSON_MEMBER
    #define StaticMember
    #define StaticPrefix(structName, constructorName) structName::constructorName
    #define Namespaced(value) AntJson::value
#else
    #define Namespaced(value) value
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
    #ifdef ANT_JSON_MEMBER
        #define AntFromJsonName(structName) fromJson
    #else
        #define AntFromJsonName(structName) structName##FromJson
    #endif // ANT_JSON_MEMBER
#endif // AntFromJsonName

#ifndef AntToJsonSchemeName
    #ifdef ANT_JSON_MEMBER
        #define AntToJsonSchemeName(structName) toJsonScheme
    #else
        #define AntToJsonSchemeName(structName) structName##ToJsonScheme
    #endif // ANT_JSON_MEMBER
#endif // AntToJsonSchemeName


#ifndef AntChildrenUnpackName
#define AntChildrenUnpackName(structName) _children__unpack__##structName
#endif // AntChildrenUnpackName


#ifndef AntStruct
#define AntStruct(jsonKey, fieldName, type)                                  \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        StaticPrefix(type, AntFromJsonName(type))(source, dest->fieldName);             \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        StaticPrefix(type, AntFromJsonName(type))(source->children[i], dest->fieldName);\
    }                                                                                   \
    if (flag == 2) {                                                                    \
        Namespaced(JsonNode)* child = StaticPrefix(type, AntToJsonSchemeName(type))();              \
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
        Namespaced(JsonNode)* child = getEmptyJsonNode(AntKeySecure(jsonKey), nodeType);            \
        addChild(parent, child);                                                        \
    }
#endif // AntValue

#ifndef AntJson
#define AntJson(structType, ...)                                                 \
    StaticMember AntChildrenUnpack(structType, ##__VA_ARGS__)\
    int StaticPrefix(structType, AntFromJsonName(structType))(Namespaced(JsonNode)* source, structType* dest) {  \
        if (source->type == Namespaced(JsonNodeTypeObject)) {                                       \
            AntChildrenUnpackName(structType)(source, dest);                            \
        }                                                                               \
        const int flag = 0;                                                             \
        const int i = 0;                                                                \
        Namespaced(JsonNode)* parent = NULL;                                                        \
        __VA_ARGS__                                                                     \
        return 0;                                                                       \
    }                                                                                   \
    Namespaced(JsonNode)* StaticPrefix(structType, AntToJsonSchemeName(structType)) () {                         \
        const int flag = 2;                                                             \
        Namespaced(JsonNode)* source = NULL;                                                        \
        structType* dest = NULL;                                                        \
        const int i = 0;                                                                \
        Namespaced(JsonNode)* parent = getEmptyJsonNode(AntKeySecure(""), Namespaced(JsonNodeTypeObject));      \
        __VA_ARGS__                                                                     \
        return parent;                                                                  \
    }                                                                                   \

#endif // AntJson

#ifndef AntChildrenUnpack
#define AntChildrenUnpack(structType, ...)                                              \
    int AntChildrenUnpackName(structType)(Namespaced(JsonNode)* source, structType* dest) {         \
        const int flag = 1;                                                             \
        Namespaced(JsonNode)* parent = NULL;                                                        \
        if (source->type != Namespaced(JsonNodeTypeObject)) {                                       \
            return -1;                                                                  \
        }                                                                               \
        for (int i = 0; i < source->childrenLength; i++) {                              \
            __VA_ARGS__                                                                 \
        }                                                                               \
        return 0;                                                                       \
    }
#endif // AntChildrenUnpack