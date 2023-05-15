#define ANT_JSON_MEMBER
#include "../../antjson.h"
#include <iostream>

struct Account {
    char* username;
    char* password;

    // Needed declaration for macro usage
    static int fromJson(Ant::JsonNode *source, Account *dest);
    static Ant::JsonNode *toJsonScheme();
};
AntJson(Account,
        // Macro for member type if it's primitive and not object
        AntValue("username", username, AntString)
        AntValue("password", password, AntString)
)

//AntValueTest("password", password, Ant::JsonNodeType::String)

struct NVR {
    char* ip;
    char* name;
    int port;
    Account* account;

    // Needed declaration for macro usage
    static int fromJson(Ant::JsonNode* source, NVR* dest);
    static Ant::JsonNode* toJsonScheme();
};

AntJson(NVR,
        // Macro for member type if it's primitive and not object
        AntValue("ip", ip, AntString)
        AntValue("name", name, AntString)
        AntValue("port", port, AntInt)
        // Macro for member type if it's sub-struct
        AntStruct("account", account, Account)
)

void parser(const char* json) {
    NVR nvr;
    // Parse scheme with meta from given JSON
    Ant::JsonNode* jsonScheme = Ant::jsonNodeParse(json);
    // Get JSON schema from DTO that we need to parse in
    Ant::JsonNode* dtoScheme = NVR::toJsonScheme();
    // When we have both schemas we can compare them
    if (Ant::jsonIsEqualScheme(jsonScheme, dtoScheme)) {
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

    Ant::JsonNode* parsedJsonNode = Ant::jsonNodeParse(cc);
    Ant::JsonNode* parsedJsonNode2 = NVR::toJsonScheme();


    NVR::fromJson(parsedJsonNode, &nvr);
    if (jsonIsEqualScheme(parsedJsonNode, parsedJsonNode2)) {
        std::cout << "Equals" << "\n";
    } else {
        std::cout << "No-Equals" << "\n";
    }
}