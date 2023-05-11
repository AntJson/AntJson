#define ANT_JSON_MEMBER
#include "../../antjson.h"
#include <iostream>

struct Account {
    char* username;
    char* password;
    DTOConstructor(Account,
                   DTOFieldConstructor("username", username, s, JsonNodeType::String)
                   DTOFieldConstructor("password", password, s, JsonNodeType::String)
    )
};


struct NVR {
    char* ip;
    char* name;
    int port;
    Account* account;
    DTOConstructor(NVR,
                   DTOFieldConstructor("ip", ip, s, JsonNodeTypeString)
                   DTOFieldConstructor("name", name, s, JsonNodeTypeString)
                   DTOFieldConstructor("port", port, i, JsonNodeTypeInt)
                   DTOStructConstructor("account", account, Account)
    )
};



int main() {

    const char* cc = "{\"account\":{\"password\":\"oo2929212____dsfds\",\"username\":\"somename\"},\"ip\":\"109.18.2.100\",\"name\":\"nvr4ik\",\"port\":37777}\n";

    NVR nvr;

    JsonNode* parsedJsonNode = jsonNodeParse(cc);
    JsonNode* parsedJsonNode2 = NVR::NVRToJsonScheme();

    NVR::NVRFromJson(parsedJsonNode, &nvr);
    if (jsonIsEqualScheme(parsedJsonNode, parsedJsonNode2)) {
        std::cout << "Equals" << "\n";
    } else {
        std::cout << "No-Equals" << "\n";
    }
}