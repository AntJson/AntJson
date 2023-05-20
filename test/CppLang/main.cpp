#define ANT_JSON_MEMBER
#include <iostream>
#include "dtos/nvr/nvr.h"

int main() {

    const char* json = "{\n"
                       "  \"account\":{\n"
                       "    \"password\":\"oo2929212____dsfds\",\n"
                       "    \"username\":\"somename\"\n"
                       "  },\n"
                       "  \"ip\":\"109.18.2.100\",\n"
                       "  \"name\":\"nvr4ik\",\n"
                       "  \"port\":37777,\n"
                       "  \"numbersArray\": [1, 2, 3, 4],\n"
                       "  \"accountArray\": [\n"
                       "    {\n"
                       "      \"password\":\"oo2929212____dsfds\",\n"
                       "      \"username\":\"somename\"\n"
                       "    }\n"
                       "    {\n"
                       "      \"password\":\"oo2929212____dsfds\",\n"
                       "      \"username\":\"somename\"\n"
                       "    }\n"
                       "  ]\n"
                       "}";

    if (NVR::isEqualScheme(json)) {
        std::cout << "Equals" << "\n";
    } else {
        std::cout << "No-Equals" << "\n";
    }
    NVR nvr(json);

    return 0;
}