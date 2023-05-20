#ifndef ANTJSON_ACCOUNT_H
#define ANTJSON_ACCOUNT_H

#include <string>
#include <antjson.h>

struct Account {
    std::string username;
    std::string password;

    Account() = default;
    explicit Account(const std::string& json);
    static int isEqualScheme(const std::string& json);

    static inline int fromJson(Ant::JsonNode* source, Account* dest);
    static inline Ant::JsonNode* toJsonScheme();
};

#endif //ANTJSON_ACCOUNT_H
