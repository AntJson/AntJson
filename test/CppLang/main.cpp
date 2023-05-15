#define ANT_JSON_MEMBER
#include "../../antjson.h"
#include <iostream>
#include <vector>

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

struct NVR {
    char* ip;
    char* name;
    int port;
    Account account;
    std::vector<int> numbersArray;

    // Needed declaration for macro usage
    static int fromJson(Ant::JsonNode* source, NVR* dest);
    static Ant::JsonNode* toJsonScheme();
};

AntJson(NVR,
        // Macro for member type if it's primitive and not object
        AntValue("ip", ip, AntString)
        AntValue("name", name, AntString)
        AntValue("port", port, AntInt)
        AntValue("test", numbersArray, AntArray, AntInt)
        // Macro for member type if it's sub-struct
        AntStruct("account", account, Account)
)



int main() {

    const char* cc = "{\"account\":{\"password\":\"oo2929212____dsfds\",\"username\":\"somename\"},\"ip\":\"109.18.2.100\",\"name\":\"nvr4ik\",\"port\":37777, \"test\": [1, 2, 3, 4]}\n";

    NVR nvr;

    Ant::JsonNode* parsedJsonNode = Ant::jsonNodeParse(cc);
    Ant::JsonNode* parsedJsonNode2 = NVR::toJsonScheme();

    NVR::fromJson(parsedJsonNode, &nvr);
    if (jsonIsEqualScheme(parsedJsonNode, parsedJsonNode2)) {
        std::cout << "Equals" << "\n";
    } else {
        std::cout << "No-Equals" << "\n";
    }

    return 0;
}