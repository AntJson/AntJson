#define JSMN_PARENT_LINKS
#include "../antjson.h"
#include "structures/user-struct.h"


int main() {
    const char* complex = "{\n"
                          "  \"age\": 15,\n"
                          "  \"profile\": {\n"
                          "    \"married\": true,\n"
                          "    \"contacts\" : {\n"
                          "      \"number\": \"null\"\n"
                          "    }\n"
                          "  }\n"
                          "}";

    User* user = (User*) malloc(sizeof(User));
    user->profile = (Profile*) malloc(sizeof(Profile));
    user->profile->contacts = (Contacts*)malloc(sizeof (Contacts));

    JsonNode* parsedJsonNode = jsonNodeParse(complex);
    JsonNode* parsedJsonNode2 = UserToJsonScheme();
    UserFromJson(parsedJsonNode, user);

    if (jsonIsEqualScheme(parsedJsonNode, parsedJsonNode2)) {
        printf("Equals\n");
    } else {
        printf("No-Equals\n");
    }
}