#ifndef ANTJSON_NVR_H
#define ANTJSON_NVR_H

#include <string>
#include <vector>
#include <antjson.h>
#include "../account/account.h"

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

    static int fromJson(Ant::JsonNode* source, NVR* dest);
    static inline Ant::JsonNode* toJsonScheme();
};

#endif //ANTJSON_NVR_H
