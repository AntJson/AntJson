#include "../json-node/json.h"
#include "../json-parser/json-parser.h"

#ifdef ANT_JSON_MEMBER
    #define StaticMember static
    #define StaticPrefix(structName, constructorName) structName::constructorName
#else
    #define ConstructorPrefix(fieldName, constructorName) constructorName
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

#ifndef DTOKeySecure
    #ifdef __cplusplus
        #define DTOKeySecure(jsonKey) (char*)jsonKey
    #else
        #define DTOKeySecure(jsonKey) jsonKey
    #endif // __cplusplus
#endif // DTOKeySecure


#ifndef DTOFromJsonName
#define DTOFromJsonName(structName) structName##FromJson
#endif // DTOFromJsonName

#ifndef DTOChildrenUnpackName
#define DTOChildrenUnpackName(structName) _children__unpack__##structName
#endif // DTOChildrenUnpackName

#ifndef DTOToJsonSchemeName
#define DTOToJsonSchemeName(structName) structName##ToJsonScheme
#endif // DTOToJsonSchemeName

#ifndef DTOStructConstructor
#define DTOStructConstructor(jsonKey, fieldName, type)                                  \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        StaticPrefix(type, DTOFromJsonName(type))(source, dest->fieldName);             \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        StaticPrefix(type, DTOFromJsonName(type))(source->children[i], dest->fieldName);\
    }                                                                                   \
    if (flag == 2) {                                                                    \
        JsonNode* child = StaticPrefix(type, DTOToJsonSchemeName(type))();              \
        child->key = DTOKeySecure(jsonKey);                                             \
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
        JsonNode* child = getEmptyJsonNode(DTOKeySecure(jsonKey), nodeType);            \
        addChild(parent, child);                                                        \
    }
#endif // DTOFieldConstructor

#ifndef DTOConstructor
#define DTOConstructor(structType, ...)                                                 \
    StaticMember DTOChildrenUnpack(structType, ##__VA_ARGS__)\
    StaticMember int DTOFromJsonName(structType)(JsonNode* source, structType* dest) {  \
        if (source->type == JsonNodeTypeObject) {                                       \
            DTOChildrenUnpackName(structType)(source, dest);                            \
        }                                                                               \
        const int flag = 0;                                                             \
        const int i = 0;                                                                \
        JsonNode* parent = NULL;                                                        \
        __VA_ARGS__                                                                     \
        return 0;                                                                       \
    }                                                                                   \
    StaticMember JsonNode* DTOToJsonSchemeName(structType) () {                         \
        const int flag = 2;                                                             \
        JsonNode* source = NULL;                                                        \
        structType* dest = NULL;                                                        \
        const int i = 0;                                                                \
        JsonNode* parent = getEmptyJsonNode(DTOKeySecure(""), JsonNodeTypeObject);      \
        __VA_ARGS__                                                                     \
        return parent;                                                                  \
    }                                                                                   \

#endif // DTOConstructor

#ifndef DTOChildrenUnpack
#define DTOChildrenUnpack(structType, ...)                                              \
    int DTOChildrenUnpackName(structType)(JsonNode* source, structType* dest) {         \
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
#endif // DTOChildrenUnpack