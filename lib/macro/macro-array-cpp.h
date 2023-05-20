#ifndef ANTJSON_MACRO_ARRAY_CPP_H
#define ANTJSON_MACRO_ARRAY_CPP_H
#include "macro-cpp.h"

#ifndef AntPushArrayChild
#define AntPushArrayChild(source, field, value) source->field.push_back(value)

#endif // AntPushArrayChild

#ifndef AntStructArray
#define AntStructArray(jsonKey, field, arrType) \
    if (flag == 0 && !strcmp(source->key, jsonKey)) { \
        if (source->type == AntJsonNodeType(Array)) {\
          for (int j = 0; j < source->childrenLength; j++) {                         \
                arrType child;                  \
                AntFromJsonName(arrType)(source->children[j], &child);    \
                AntPushArrayChild(dest, field, child);\
            }\
        }\
    }                                            \
    if (flag == 1 && !strcmp(source->children[i]->key, jsonKey)) {                     \
        if (source->children[i]->type == AntJsonNodeType(Array)) {                     \
            for (int j = 0; j < source->children[i]->childrenLength; j++) {                         \
                arrType child;                  \
                AntFromJsonName(arrType)(source->children[i]->children[j], &child);    \
                AntPushArrayChild(dest, field, child);\
            }\
        }\
    }                                           \
    if (flag == 2) {                            \
        Namespaced(JsonNode)* child = getEmptyJsonNode(AntKeySecure(jsonKey), AntJsonNodeType(Array)); \
        child->arrayElementsType = AntJsonNodeType(Object);\
        addChild(parent, child);                \
        Namespaced(JsonNode)* arrChild = AntToJsonSchemeName(arrType)();             \
        addChild(child, arrChild);\
    }\


#endif // AntStructArray
#endif //ANTJSON_MACRO_ARRAY_CPP_H
