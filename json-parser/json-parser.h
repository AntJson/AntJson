//
// Created by danysmall on 5/11/23.
//

#include <stdint.h>
#include "../json-node/json.h"
#include "../jsmn/jsmn.h"

#ifndef DTOCONSTRUCTOR_JSON_PARSER_H
#define DTOCONSTRUCTOR_JSON_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

JsonNode* jsonNodeParse(const char* source);

#ifdef __cplusplus
};
#endif

#endif //DTOCONSTRUCTOR_JSON_PARSER_H