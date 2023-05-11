#include "complexity-tests/nested-structs.h"
#include "complexity-tests/simple-struct.h"
#include "json-parser/json-token-test.h"
#include "json-parser/tokenizer/tokenizer.h"
#include "json-parser/node-converter/node-converter.h"

#define JSMN_PARENT_LINKS
#include "jsmn/jsmn.h"
#include "json-node/json-macro.h"

typedef struct {
    char* number;
} Contacts;
DTOConstructor(Contacts,
               DTOFieldConstructor("number", number, s))

typedef struct {
    int married;
    Contacts* contacts;
} Profile;
DTOConstructor(Profile,
               DTOFieldConstructor("married", married, b)
               DTOStructConstructor("contacts", contacts, Contacts))

typedef struct {
    int age;
    Profile* profile;
} User;
DTOConstructor(User,
               DTOFieldConstructor("age", age, i)
               DTOStructConstructor("profile", profile, Profile))

const char* complex = "{\n"
                      "  \"age\": 15,\n"
                      "  \"profile\": {\n"
                      "    \"married\": true,\n"
                      "    \"contacts\" : {\n"
                      "      \"number\": null\n"
                      "    }\n"
                      "  }\n"
                      "}";


int tokensToNodes(jsmntok_t* tokens, uint32_t tokensCount, JsonNode* node, const char* source) {
    for (uint32_t i = 0; i < tokensCount; i += 2) {
        jsmntok_t key = tokens[i];
        jsmntok_t value = tokens[i + 1];

        if (value.type == JSMN_STRING) {
            JsonNode* child = getEmptyJsonNode(
                    getSubstr(source, key.start, key.end),
                    string);
            child->value.s = getSubstr(source, value.start, value.end);
            addChild(node, child);
            continue;
        }

        if (value.type == JSMN_PRIMITIVE) {
            JsonNode* child = getEmptyJsonNode(
                    getSubstr(source, key.start, key.end),
                    object);
            addChild(node, child);

            char* valueString = getSubstr(source, value.start, value.end);
            if (valueString[0] == 'n') {
                child->type = null;
                child->value.s = NULL;
            } else if (valueString[0] == 't') {
                child->type = bool;
                child->value.b = 1;
            } else if (valueString[0] == 'f') {
                child->type = bool;
                child->value.b = 0;
            } else {
                if (strstr(valueString, ".")) {
                    child->type = number_f;
                    child->value.f = atof(valueString);
                } else {
                    child->type = number_i;
                    child->value.i = atoi(valueString);
                }
            }

            continue;
        }

        if (value.type == JSMN_OBJECT) {
            JsonNode* child = getEmptyJsonNode(
                    getSubstr(source, key.start, key.end),
                    object);
            addChild(node, child);

            jsmntok_t objectTokens[tokensCount - i];
            memcpy(objectTokens, tokens + i + 2, (tokensCount - i - 3) * sizeof(*tokens));
            i += tokensToNodes(objectTokens, tokensCount - i - 3, child, source);
            continue;
        }
    }
    return tokensCount;
}

int main() {
    jsmn_parser p;
    jsmntok_t t[128]; /* We expect no more than 128 JSON tokens */

    jsmn_init(&p);
    int response = jsmn_parse(&p, complex, strlen(complex), t, 128);
    jsmntok_t tokens[128];
    memcpy(tokens, t + 1, (response - 1) * sizeof(jsmntok_t));

    JsonNode* node = getEmptyJsonNode("", object);
    tokensToNodes(tokens, response, node, complex);

    User* user = (User*) malloc(sizeof(User));
    user->profile = (Profile*) malloc(sizeof(Profile));
    user->profile->contacts = (Contacts*)malloc(sizeof (Contacts));

    __constructor__User(node, user);
}