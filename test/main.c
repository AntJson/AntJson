#include "../antjson.h"
#include "structures/user-struct.h"

typedef struct Account_s {
    char* username;
    char* password;
} Account;

DTOConstructor(Account,
               DTOFieldConstructor("username", username, s, string)
               DTOFieldConstructor("password", password, s, string)
)

typedef struct NVR_s {
    char* ip;
    char* name;
    int port;
    Account* account;
} NVR;
DTOConstructor(NVR,
               DTOFieldConstructor("ip", ip, s, string)
               DTOFieldConstructor("name", name, s, string)
               DTOFieldConstructor("port", port, i, number_i)
               DTOStructConstructor("account", account, Account)
)



int main() {
//    const char* complex = "{"
//                          "  \"age\": 15,"
//                          "  \"profile\": {"
//                          "    \"married\": true,"
//                          "    \"contacts\" : {"
//                          "      \"number\": \"5\""
//                          "    }"
//                          "  }"
//                          "}";
//
//    const char* cc = "{\"account\":{"
//               "\"password\":\"oo2929212____dsfds\","
//               "\"username\":\"somename\""
//               "},"
//               "\"ip\":\"109.18.2.100\","
//               "\"name\":\"nvr4ik\","
//               "\"port\":37777}\n";

    const char* cc = "{\"account\":{\"password\":\"oo2929212____dsfds\",\"username\":\"somename\"},\"ip\":\"109.18.2.100\",\"name\":\"nvr4ik\",\"port\":37777}\n";

//    User* user = (User*) malloc(sizeof(User));
//    user->profile = (Profile*) malloc(sizeof(Profile));
//    user->profile->contacts = (Contacts*)malloc(sizeof (Contacts));
    NVR* nvr = (NVR*)malloc(sizeof (NVR));
    Account* acc = (Account*)malloc(sizeof (Account));
    nvr->account = acc;

    JsonNode* parsedJsonNode = jsonNodeParse(cc);
    JsonNode* parsedJsonNode2 = NVRToJsonScheme();
    NVRFromJson(parsedJsonNode, nvr);

    if (jsonIsEqualScheme(parsedJsonNode, parsedJsonNode2)) {
        printf("Equals\n");
    } else {
        printf("No-Equals\n");
    }
}