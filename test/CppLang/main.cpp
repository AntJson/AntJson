#include "../../antjson.h"
#include <iostream>

typedef struct Account_s {
    char* username;
    char* password;
} Account;

DTOConstructor(Account,
               DTOFieldConstructor("username", username, s, JsonNodeType::String)
               DTOFieldConstructor("password", password, s, JsonNodeType::String)
)

typedef struct NVR_s {
    char* ip;
    char* name;
    int port;
    Account* account;
} NVR;
DTOConstructor(NVR,
               DTOFieldConstructor("ip", ip, s, JsonNodeTypeString)
               DTOFieldConstructor("name", name, s, JsonNodeTypeString)
               DTOFieldConstructor("port", port, i, JsonNodeTypeInt)
               DTOStructConstructor("account", account, Account)
)


int main() {

    const char* cc = "{\"account\":{\"password\":\"oo2929212____dsfds\",\"username\":\"somename\"},\"ip\":\"109.18.2.100\",\"name\":\"nvr4ik\",\"port\":37777}\n";

    NVR nvr;

    JsonNode* parsedJsonNode = jsonNodeParse(cc);
    JsonNode* parsedJsonNode2 = NVRToJsonScheme();
    NVRFromJson(parsedJsonNode, &nvr);
    if (jsonIsEqualScheme(parsedJsonNode, parsedJsonNode2)) {
        printf("Equals\n");
    } else {
        printf("No-Equals\n");
    }
}