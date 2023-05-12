#define ANT_JSON_MEMBER
#include "../../antjson.h"
#include <iostream>

struct Account {
    char* username;
    char* password;
    static int fromJson(AntJson::JsonNode *source, Account *dest);
    static AntJson::JsonNode *toJsonScheme();
};
AntJson(Account,
        AntValue("username", username, s, AntJson::JsonNodeType::String)
        AntValue("password", password, s, AntJson::JsonNodeType::String)
)

//int Account::AccountFromJson(JsonNode *source, Account *dest) {}
//JsonNode* Account::AccountToJsonScheme() {}

struct NVR {
    char* ip;
    char* name;
    int port;
    Account* account;
    static int fromJson(AntJson::JsonNode* source, NVR* dest);
    static AntJson::JsonNode* toJsonScheme();
};

AntJson(NVR,
        AntValue("ip", ip, s, AntJson::JsonNodeType::String)
        AntValue("name", name, s, AntJson::JsonNodeType::String)
        AntValue("port", port, i, AntJson::JsonNodeType::Int)
        AntStruct("account", account, Account)
)

void parser(const char* json) {
    NVR nvr;
    // Parse scheme with meta from given JSON
    AntJson::JsonNode* jsonScheme = AntJson::jsonNodeParse(json);
    // Get JSON schema from DTO that we need to parse in
    AntJson::JsonNode* dtoScheme = NVR::toJsonScheme();
    // When we have both schemas we can compare them
    if (AntJson::jsonIsEqualScheme(jsonScheme, dtoScheme)) {
        // If schemas are equals we can parse it now and be sure
        // that parsing will be successful
        NVR::fromJson(jsonScheme, &nvr);
    } else {
        // If schemas are different throw error
        throw;
    }

}

int main() {

    const char* cc = "{\"account\":{\"password\":\"oo2929212____dsfds\",\"username\":\"somename\"},\"ip\":\"109.18.2.100\",\"name\":\"nvr4ik\",\"port\":37777}\n";

    NVR nvr;

    AntJson::JsonNode* parsedJsonNode = AntJson::jsonNodeParse(cc);
    AntJson::JsonNode* parsedJsonNode2 = NVR::toJsonScheme();


    NVR::fromJson(parsedJsonNode, &nvr);
    if (jsonIsEqualScheme(parsedJsonNode, parsedJsonNode2)) {
        std::cout << "Equals" << "\n";
    } else {
        std::cout << "No-Equals" << "\n";
    }
}