#include "json.h"
#include <string.h>
#include <stdlib.h>

#ifndef DTOFieldSetGet
#define DTOFieldSetGet(structType, type, fieldName, keyName) \
    int __set__##structType##__##fieldName( structType* source, char* key, type value ) { \
        if (!strcmp(key, keyName)) { \
            source->fieldName = value; \
            return 0; \
        } \
        return -1; \
    } \
    type __get__##structType##__##fieldName( structType* source ) { \
        return source->fieldName; \
    }
#endif // DTOFieldSetGet

#ifndef DTOStructConstructor
#define DTOStructConstructor(jsonKey, fieldName, type)                                  \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        __constructor__##type(source, dest->fieldName);                                 \
    }                                                                                   \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                      \
        __constructor__##type(source->children[i], dest->fieldName);                    \
    }
#endif // DTOStructConstructor

#ifndef DTOFieldConstructor
#define DTOFieldConstructor(jsonKey, fieldName, unionType)                              \
    if (flag == 0 && !strcmp(source->key, jsonKey)) {                                   \
        dest->fieldName = source->value.unionType;                                      \
    } \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) { \
        dest->fieldName = source->children[i]->value.unionType; \
    }
#endif // DTOFieldConstructor

#ifndef DTOConstructor
#define DTOConstructor(structType, ...)                                                 \
    DTOChildrenUnpack(structType, ##__VA_ARGS__)                                        \
    int __constructor__##structType(JsonNode* source, structType* dest) {               \
        if (source->type == object) {                                                   \
            __children__unpack__##structType(source, dest);                             \
        }                                                                               \
        int flag = 0;                                                                   \
        int i = 0;                                                                      \
        __VA_ARGS__                                                                     \
        return 0;                                                                       \
    }
#endif // DTOConstructor

#ifndef DTOChildrenUnpack
#define DTOChildrenUnpack(structType, ...)                                              \
    int __children__unpack__##structType(JsonNode* source, structType* dest) {          \
        int flag = 1;                                                                   \
        if (source->type != object) {                                                   \
            return -1;                                                                  \
        }                                                                               \
        for (int i = 0; i < source->childrenLength; i++) {                              \
            __VA_ARGS__                                                                 \
        }                                                                               \
        return 0;                                                                       \
    }
#endif // DTOChildrenUnpack