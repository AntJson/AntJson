#include <string.h>
#include <stdio.h>
#include "json.h"

#define DTOField(structType, type, fieldName, keyName) \
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

#define DTOFieldConstructor(jkey, fieldName, unionType) \
    if (!strcmp(source->key, jkey)) { \
        dest->fieldName = source->value.unionType; \
    }

#define DTOConstructor(structType, ...) \
    int __constructor__##structType(JsonNode* source, structType* dest) { \
        if (source->type == object) { \
            for (int i = 0; i < source->childrenLength; i++) { \
                __constructor__##structType(source->children[i], dest); \
            } \
            return 0; \
        } \
        __VA_ARGS__ \
        return 0; \
    }