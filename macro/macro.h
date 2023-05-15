#include "../json-node/json.h"
#include "../json-parser/json-parser.h"

#ifndef AntString
#define AntString String
#endif

#ifndef AntInt
#define AntInt Int
#endif

#ifndef AntFloat
#define AntFloat Float
#endif

#ifndef AntBool
#define AntBool Bool
#endif

#ifndef AntUnionType
    #define AntUnionType(cond) AntUnionType ## cond
    #define AntUnionTypeString s
    #define AntUnionTypeInt i
    #define AntUnionTypeFloat f
    #define AntUnionTypeBool b
#endif // AntUnionType

#ifndef AntJsonNodeType
    #ifdef __cplusplus
        #define AntJsonNodeType(cond) AntJsonNodeType ## cond
        #define AntJsonNodeTypeString Ant::JsonNodeType::String
        #define AntJsonNodeTypeInt Ant::JsonNodeType::Int
        #define AntJsonNodeTypeFloat Ant::JsonNodeType::Float
        #define AntJsonNodeTypeBool Ant::JsonNodeType::Bool
    #else
        #define AntJsonNodeType(cond) JsonNodeType ## cond
    #endif // __cplusplus
#endif // AntJsonNodeType

#ifdef ANT_JSON_MEMBER
    #define StaticMember
    #define StaticPrefix(structName, constructorName) structName::constructorName
    #define Namespaced(value) Ant::value
    #define JsonType(type) JsonNodeType::type
#else
    #define Namespaced(value) value
    #define StaticMember
    #define StaticPrefix(structName, constructorName) constructorName
    #define JsonType(type) JsonNodeType##type
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
#define AntValue(jsonKey, fieldName, nodeType)                                     \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        dest->fieldName = source->value.AntUnionType(nodeType);                         \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        dest->fieldName = source->children[i]->value.AntUnionType(nodeType);            \
    }                                                                                   \
    if (flag == 2) {                                                                    \
        Namespaced(JsonNode)* child = getEmptyJsonNode(AntKeySecure(jsonKey), AntJsonNodeType(nodeType));\
        addChild(parent, child);                                                        \
    }
#endif // AntValue

#ifndef AntJson
#define AntJson(structType, ...)                                                 \
    StaticMember AntChildrenUnpack(structType, ##__VA_ARGS__)\
    int StaticPrefix(structType, AntFromJsonName(structType))(Namespaced(JsonNode)* source, structType* dest) {  \
        if (source->type == Namespaced(JsonType(Object))) {                                       \
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
        Namespaced(JsonNode)* parent = getEmptyJsonNode(AntKeySecure(""), Namespaced(JsonType(Object)));      \
        __VA_ARGS__                                                                     \
        return parent;                                                                  \
    }                                                                                   \

#endif // AntJson

#ifndef AntChildrenUnpack
#define AntChildrenUnpack(structType, ...)                                              \
    int AntChildrenUnpackName(structType)(Namespaced(JsonNode)* source, structType* dest) {         \
        const int flag = 1;                                                             \
        Namespaced(JsonNode)* parent = NULL;                                                        \
        if (source->type != Namespaced(JsonType(Object))) {                                       \
            return -1;                                                                  \
        }                                                                               \
        for (int i = 0; i < source->childrenLength; i++) {                              \
            __VA_ARGS__                                                                 \
        }                                                                               \
        return 0;                                                                       \
    }
#endif // AntChildrenUnpack