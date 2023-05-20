#ifndef ANTJSON_I_JSON_PARSER_H
#define ANTJSON_I_JSON_PARSER_H
#include <string>
#include "../json-node/json.h"

class IJsonParser {
public:
    virtual Ant::JsonNode* parse() = 0;
};

#endif // ANTJSON_I_JSON_PARSER_H
