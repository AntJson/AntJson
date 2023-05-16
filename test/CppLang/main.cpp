#define ANT_JSON_MEMBER
#include <iostream>
#include <fstream>
#include <vector>
#include "../../antjson.h"
#include "../../macro/macro-array-cpp.h"
struct Account {
    std::string username;
    std::string password;

    Account() = default;
    explicit Account(const std::string& json);
    static int isEqualScheme(const std::string& json);
};
AntJson(Account,
        // Macro for member type if it's primitive and not object
        AntValue("username", username, AntString)
        AntValue("password", password, AntString)
)

struct NVR {
    std::string ip{};
    std::string name{};
    int port{};
    Account account{};
    std::vector<int> numbersArray;
    std::vector<Account> accountArray;

    NVR() = default;
    explicit NVR(const std::string& json);
    static int isEqualScheme(const std::string& json);
};

AntJson(NVR,
        // Macro for member type if it's primitive and not object
        AntValue("ip", ip, AntString)
        AntValue("name", name, AntString)
        AntValue("port", port, AntInt)
        AntValue("numbersArray", numbersArray, AntArray, AntInt)
        // Array with struct template type
        AntStructArray("accountArray", accountArray, Account)
        // Macro for member type if it's sub-struct
        AntStruct("account", account, Account)
)


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
        NVR nvr(json);
    } else {
        std::cout << "No-Equals" << "\n";
    }

    return 0;
}