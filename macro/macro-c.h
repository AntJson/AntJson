#include "../json-node/json.h"
#include "../json-parser/json-parser.h"

#ifdef ANT_USE_REFERENCES
    #define AntReference(exp) &exp
#else
    #define AntReference(exp) exp
#endif // ANT_USE_REFERENCES

#ifdef ANT_USE_VECTOR
    #define AntArrayAppend(array, value, index) array.push_back(value)
#else
    #define AntArrayAppend(array, value, index) array[index] = value
#endif // ANT_USE_VECTOR

#ifndef AntTypes
#define AntTypes

#define AntString String
#define AntInt Int
#define AntFloat Float
#define AntBool Bool
#define AntArray Array

#endif // AntTypes

#ifndef AntTypeCast
#define AntTypeCast(cond) AntTypeCast ## cond
#define AntTypeCastString (char*)
#define AntTypeCastInt (int)
#define AntTypeCastFloat (float)
#define AntTypeCastBool (int)
#define AntTypeCastArray
#endif

#ifndef AntUnionType
#define AntUnionType(cond, ...) AntUnionType ## cond
#define AntUnionTypeString(...) s
#define AntUnionTypeInt(...) i
#define AntUnionTypeFloat(...) f
#define AntUnionTypeBool(...) b
#define AntUnionTypeArray(...) AntUnionType ## __VA_ARGS__()
#endif // AntUnionType

#ifndef AntJsonNodeType
#ifdef __cplusplus
#define AntJsonNodeType(cond) AntJsonNodeType ## cond
#define AntJsonNodeTypeString Ant::JsonNodeType::String
#define AntJsonNodeTypeInt Ant::JsonNodeType::Int
#define AntJsonNodeTypeFloat Ant::JsonNodeType::Float
#define AntJsonNodeTypeBool Ant::JsonNodeType::Bool
#define AntJsonNodeTypeArray Ant::JsonNodeType::Array
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
        StaticPrefix(type, AntFromJsonName(type))(source, AntReference(dest->fieldName));             \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        StaticPrefix(type, AntFromJsonName(type))(source->children[i], AntReference(dest->fieldName));\
    }                                                                                   \
    if (flag == 2) {                                                                    \
        Namespaced(JsonNode)* child = StaticPrefix(type, AntToJsonSchemeName(type))();              \
        child->key = AntKeySecure(jsonKey);                                             \
        addChild(parent, child);                                                        \
    }
#endif // AntStruct


#ifndef AntArrayChild
#define AntArrayChild(cond) AntArrayChild ## cond
#define AntArrayChildString(fieldName, unionType)
#define AntArrayChildInt(fieldName, unionType)
#define AntArrayChildFloat(fieldName, unionType)
#define AntArrayChildBool(fieldName, unionType)
#define AntArrayChildArray(fieldName, unionType) AntArrayAppend(dest->fieldName, source->children[i]->children[j]->value.unionType, j)
#endif // AntArrayChild

#ifndef AntArrayAssign
#define AntArrayAssign(nodeType) AntArrayAssign ## nodeType
#define AntArrayAssignInt(exp) exp
#define AntArrayAssignString(exp) exp
#define AntArrayAssignFloat(exp) exp
#define AntArrayAssignBool(exp) exp
#define AntArrayAssignArray(exp)
#endif // AntArrayAssign

#ifndef AntArrayChildrenAssign
#define AntArrayChildrenAssign(nodeType) AntArrayChildrenAssign ## nodeType
#define AntArrayChildrenAssignInt(dest, join, source) dest join source
#define AntArrayChildrenAssignString(dest, join, source) \
    dest = (char*)malloc(sizeof(char) * strlen(source));\
    strcpy(dest, source)
#define AntArrayChildrenAssignFloat(dest, join, source) dest join source
#define AntArrayChildrenAssignBool(dest, join, source) dest join source
#define AntArrayChildrenAssignArray(dest, join, source)
#endif // AntArrayChildrenAssign

#ifndef AntArrayChildrenType
#define AntArrayChildrenType(nodeType) AntArrayChildrenType_ ## nodeType

    #define AntArrayChildrenType_(type)
    #define AntArrayChildrenType_Int(type) child->arrayElementsType = type
    #define AntArrayChildrenType_String(type) child->arrayElementsType = type
    #define AntArrayChildrenType_Float(type) child->arrayElementsType = type
    #define AntArrayChildrenType_Bool(type) child->arrayElementsType = type

#endif // AntArrayChildrenType

#ifndef AntAllocArray

#define AntAllocArrayInt

#endif // AntAllocArray

#ifndef AntValue
#define AntValue(jsonKey, fieldName, nodeType, ...)                                     \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                              \
        AntArrayAssign(nodeType)(dest->fieldName = source->value.AntUnionType(nodeType)(__VA_ARGS__));\
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        if (source->children[i]->type == AntJsonNodeType(Array)) {                           \
            for (int j = 0; j < source->children[i]->childrenLength; j++) {                      \
                AntArrayChild(nodeType)(fieldName, AntUnionType(nodeType)(__VA_ARGS__)); \
            }                                                                      \
        }                                                                               \
        AntArrayChildrenAssign(nodeType)(dest->fieldName, =, source->children[i]->value.AntUnionType(nodeType)(__VA_ARGS__));            \
    }                                                                                   \
    if (flag == 2) {                                                                    \
        Namespaced(JsonNode)* child = getEmptyJsonNode(AntKeySecure(jsonKey), AntJsonNodeType(nodeType));                                \
        AntArrayChildrenType(__VA_ARGS__)(AntJsonNodeType(__VA_ARGS__));\
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