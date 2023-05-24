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
#define AntKeySecure(jsonKey) jsonKey
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
    if (flag == 2) {                                                                    \
        Namespaced(JsonNode)* child = AntToJsonSchemeName(type)();           \
        Namespaced(addKey)(child, jsonKey);\
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

#ifndef AntAppendIf
#define AntAppendIf(exp) AntAppendIf ## exp
#define AntAppendIfInt(exp)
#define AntAppendIfString(exp)
#define AntAppendIfFloat(exp)
#define AntAppendIfBool(exp)
#define AntAppendIfArray(exp) exp
#endif // AntAppendIf

#ifndef AntAssignIf
#define AntAssignIf(exp) AntAssignIf ## exp
#define AntAssignIfInt(exp) exp
#define AntAssignIfString(exp) exp
#define AntAssignIfFloat(exp) exp
#define AntAssignIfBool(exp) exp
#define AntAssignIfArray(exp)
#endif // AntAssignIf

#ifndef AntFieldAssign
#define AntFieldAssign(exp) AntFieldAssign ## exp

#define AntFieldAssignInt(exp, ...) exp
#define AntFieldAssignString(exp, source, value) source.assign(value)
#define AntFieldAssignFloat(exp, ...) exp
#define AntFieldAssignBool(exp, ...) exp
#define AntFieldAssignArray(exp, ...) exp

#endif // AntFieldAssign

#ifndef AntValue
#define AntValue(jsonKey, fieldName, nodeType, ...)         \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                                   \
        AntAssignIf(nodeType)(AntArrayAssign(nodeType)(AntFieldAssign(nodeType)(dest->fieldName = source->value.AntUnionType(nodeType)(__VA_ARGS__), dest->fieldName, source->value.AntUnionType(nodeType)(__VA_ARGS__)));)  \
        AntAppendIf(nodeType)(if (source->type == AntJsonNodeType(Array)) { \
            for (int i = 0; i < source->childrenLength; i++) {\
                AntArrayAppend(dest->numbersArray, source->children[i]->value.AntUnionType(nodeType)(__VA_ARGS__), i);\
            }\
        })\
    }\
    if (flag == 2) {                                        \
        Namespaced(JsonNode)* child = getEmptyJsonNode(jsonKey, AntJsonNodeType(nodeType));   \
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
        Namespaced(JsonNode)* parent = getEmptyJsonNode(AntKeySecure(""), Namespaced(JsonType(Object)));    \
        AntChildrenUnpackName(structType)(nullptr, nullptr, parent, 2);                                         \
        return parent;                                                                                      \
    }
#endif // AntToJsonSchema


#ifndef AntFromJson
#define AntFromJson(structType, ...)                                                            \
    inline int AntFromJsonName(structType)(Namespaced(JsonNode)* source, structType* dest) {    \
        if (source->type == Namespaced(JsonType(Object))) {                                     \
            AntChildrenUnpackName(structType)(source, dest, nullptr, 1);                        \
            return 0;\
        }                                                                                       \
        AntChildrenUnpackName(structType)(source, dest, nullptr, 0); \
        return 0;                                                                               \
    }
#endif // AntFromJson


#ifndef AntChildrenUnpack
#define AntChildrenUnpack(structType, ...)                                              \
    inline int AntChildrenUnpackName(structType)(Namespaced(JsonNode)* source, structType* dest, Namespaced(JsonNode)    *parent, const int flag) {         \
        if (source != nullptr && source->type == Ant::JsonNodeType::Object) { \
            for (int j = 0; j < source->childrenLength; j++) { \
                AntChildrenUnpackName(structType)(source->children[j], dest, parent, 0); \
            } \
        } \
        __VA_ARGS__\
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
        Namespaced(JsonNode)* schema = Namespaced(jsonNodeParse)(json.c_str()); \
        Namespaced(JsonNode)* dtoSchema = AntToJsonSchemeName(structType)();\
        int result = Namespaced(jsonIsEqualScheme)(dtoSchema, schema);     \
        Namespaced(disposeJsonNode)(dtoSchema);\
        Namespaced(disposeJsonNode)(schema);                        \
        return result;\
    }
#endif // AntIsEqualScheme


#endif // ANT_MACRO_CPP