#ifndef ANTJSON_JSMN_PARSER_H
#define ANTJSON_JSMN_PARSER_H
#include <utility>
#include <jsmn/jsmn.h>
#include "../i-json-parser.h"

namespace Ant {
    class JsmnParser: IJsonParser {
    public:
        explicit JsmnParser(std::string json) {
            sourceJson = std::move(json);
            rootNode = Ant::getEmptyJsonNode((char*)"", Ant::JsonNodeType::Object);
        }
        Ant::JsonNode* parse() override;
    private:
        int tokensToNodes(jsmntok_t* tokens, uint32_t tokensCount, Ant::JsonNode* node, const char* src);
        int parseTokens();

        Ant::JsonNode* rootNode{};
        std::string sourceJson;

        jsmn_parser parser{};
        int parsedTokensCount{};
        jsmntok_t* parsedTokens;
    };
}


#endif // ANTJSON_JSMN_PARSER_H