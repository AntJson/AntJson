#ifndef ANT_MACRO_CPP
#define ANT_MACRO_CPP

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

#ifdef ANT_MULTI_FILE_CONSTRUCTORS
    #define AntFromJsonName(structName) structName::fromJson
    #define AntToJsonSchemeName(structName) structName::toJsonScheme
#else
    #define AntFromJsonName(structName) structName##fromJson
    #define AntToJsonSchemeName(structName) structName##ToJsonScheme
#endif

#ifndef AntUtilsDefine
    #ifdef ANT_MULTI_FILE_CONSTRUCTORS
    #define AntUtilsDefine(structType) \
            explicit structType(const std::string& json); \
            static int isEqualScheme(const std::string& json); \
            static inline int fromJson(Ant::JsonNode* source, structType* dest); \
            static inline Ant::JsonNode* toJsonScheme();
    #else
        #define AntUtilsDefine(structType) \
            explicit Account(const std::string& json); \
            static int isEqualScheme(const std::string& json);
    #endif // ANT_MULTI_FILE_CONSTRUCTORS
#endif // AntUtilsDefine

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
#define AntJsonNodeTypeObject Ant::JsonNodeType::Object
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

#ifndef AntChildrenUnpackName
#define AntChildrenUnpackName(structName) _children__unpack__##structName
#endif // AntChildrenUnpackName

#ifndef AntStruct
#define AntStruct(jsonKey, fieldName, type)                                  \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        AntFromJsonName(type)(source, AntReference(dest->fieldName));             \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        AntFromJsonName(type)(source->children[i], AntReference(dest->fieldName));\
    }                                                                                   \
    if (flag == 2) {                                                                    \
        Namespaced(JsonNode)* child = AntToJsonSchemeName(type)();              \
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
#define AntArrayChildrenAssignString(dest, join, source) dest join source
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
#define AntValue(jsonKey, fieldName, nodeType, ...)         \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                                   \
        AntArrayAssign(nodeType)(dest->fieldName = source->value.AntUnionType(nodeType)(__VA_ARGS__));  \
    }\
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                                                              \
        if (source->children[i]->type == AntJsonNodeType(Array)) {                                                              \
            for (int j = 0; j < source->children[i]->childrenLength; j++) {                                                     \
                AntArrayChild(nodeType)(fieldName, AntUnionType(nodeType)(__VA_ARGS__));                                        \
            }                                                                                                                   \
        }                                                                                                                       \
        AntArrayChildrenAssign(nodeType)(dest->fieldName, =, source->children[i]->value.AntUnionType(nodeType)(__VA_ARGS__));   \
    } \
    if (flag == 2) {                                                                                            \
        Namespaced(JsonNode)* child = getEmptyJsonNode(AntKeySecure(jsonKey), AntJsonNodeType(nodeType));   \
        AntArrayChildrenType(__VA_ARGS__)(AntJsonNodeType(__VA_ARGS__));                                    \
        addChild(parent, child);                                                                            \
    }
#endif // AntValue

#ifndef AntJson
#define AntJson(structType, ...)                    \
    AntChildrenUnpack(structType, ##__VA_ARGS__)    \
    AntFromJson(structType, ##__VA_ARGS__)          \
    AntToJsonSchema(structType, ##__VA_ARGS__)      \
    AntConstructor(structType)                      \
    AntIsEqualScheme(structType)                    \

#endif // AntJson

#ifndef AntToJsonSchema
#define AntToJsonSchema(structType, ...)                                                                    \
    inline Namespaced(JsonNode)* AntToJsonSchemeName(structType) () {                                       \
        const int flag = 2;                                                                                 \
        Namespaced(JsonNode)* source = NULL;                                                                \
        structType* dest = NULL;                                                                            \
        const int i = 0;                                                                                    \
        Namespaced(JsonNode)* parent = getEmptyJsonNode(AntKeySecure(""), Namespaced(JsonType(Object)));    \
        __VA_ARGS__                                                                                         \
        return parent;                                                                                      \
    }
#endif // AntToJsonSchema


#ifndef AntFromJson
#define AntFromJson(structType, ...)                                                            \
    inline int AntFromJsonName(structType)(Namespaced(JsonNode)* source, structType* dest) {    \
        if (source->type == Namespaced(JsonType(Object))) {                                     \
            AntChildrenUnpackName(structType)(source, dest);                                    \
        }                                                                                       \
        const int flag = 0;                                                                     \
        const int i = 0;                                                                        \
        Namespaced(JsonNode)* parent = NULL;                                                    \
        __VA_ARGS__                                                                             \
        return 0;                                                                               \
    }
#endif // AntFromJson


#ifndef AntChildrenUnpack
#define AntChildrenUnpack(structType, ...)                                              \
    inline int AntChildrenUnpackName(structType)(Namespaced(JsonNode)* source, structType* dest) {         \
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

#ifndef AntConstructor
#define AntConstructor(structType)                                              \
    structType::structType(const std::string &json) {                           \
        Namespaced(JsonNode)* schema = Namespaced(jsonNodeParse)(json.c_str()); \
        AntFromJsonName(structType)(schema, this);                              \
        Namespaced(disposeJsonNode)(schema);                                    \
    }
#endif // AntConstructor

#ifndef AntIsEqualScheme
#define AntIsEqualScheme(structType)                                \
    int structType::isEqualScheme(const std::string& json) {               \
        Namespaced(JsonNode)* schema = Namespaced(jsonNodeParse)(json.c_str());   \
        return Namespaced(jsonIsEqualScheme)(AntToJsonSchemeName(structType)(), schema);   \
    }
#endif // AntIsEqualScheme


#endif // ANT_MACRO_CPP