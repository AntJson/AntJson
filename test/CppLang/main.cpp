#define ANT_JSON_MEMBER
#include "../../antjson.h"
#include <iostream>
#include <vector>

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

    NVR() = default;
    explicit NVR(const std::string& json);
    static int isEqualScheme(const std::string& json);
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

    const char* cc = "{\"account\":{\"password\":\"oo2929212____dsfds\",\"username\":\"somename\"},\"ip\":\"109.18.2.100\",\"name\":\"nvr4ik\",\"port\":37777, \"test\": [1, 2, \"qweqwe\", 4]}\n";

    if (NVR::isEqualScheme(cc)) {
        std::cout << "Equals" << "\n";
        NVR nvr(cc);
    } else {
        std::cout << "No-Equals" << "\n";
    }

    return 0;
}