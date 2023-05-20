#ifndef DTOCONSTRUCTOR_JSON_PARSER_H
#define DTOCONSTRUCTOR_JSON_PARSER_H
#include <stdint.h>
#include "../json-node/json.h"
#include "../../third-party/jsmn/jsmn.h"

#ifdef __cplusplus
extern "C" {
    namespace Ant {
#endif

      JsonNode *jsonNodeParse(const char *source);

#ifdef __cplusplus
};};
#endif

#endif //DTOCONSTRUCTOR_JSON_PARSER_H