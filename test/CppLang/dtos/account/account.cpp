#include "account.h"

inline int _children__unpack__Account(Ant::JsonNode *source, Account *dest, Ant::JsonNode *parent, const int flag) {
    if (source != nullptr && source->type == Ant::JsonNodeType::Object) {
        for (int j = 0; j < source->childrenLength; j++) {
            _children__unpack__Account(source->children[j], dest, parent, 0);
        }
    }
    if (flag == 0 && !strcmp(source->key, "username")) {
        dest->username.assign(source->value.s);
    }
    if (flag == 2) {
        Ant::JsonNode *child = getEmptyJsonNode("username", Ant::JsonNodeType::String);;
        addChild(parent, child);
    }
    if (flag == 0 && !strcmp(source->key, "password")) {
        dest->password.assign(source->value.s);
    }
    if (flag == 2) {
        Ant::JsonNode *child = getEmptyJsonNode("password", Ant::JsonNodeType::String);;
        addChild(parent, child);
    }
    return 0;
}
inline int Account::fromJson(Ant::JsonNode *source, Account *dest) {
    if (source->type == Ant::JsonNodeType::Object) {
        _children__unpack__Account(source, dest, nullptr, 1);
        return 0;
    }
    _children__unpack__Account(source, dest, nullptr, 0);
    return 0;
}
inline Ant::JsonNode *Account::toJsonScheme() {
    Ant::JsonNode *parent = getEmptyJsonNode("", Ant::JsonNodeType::Object);
    _children__unpack__Account(nullptr, nullptr, parent, 2);
    return parent;
}
Account::Account(const std::string &json) {
    Ant::JsonNode *schema = Ant::jsonNodeParse(json.c_str());
    Account::fromJson(schema, this);
    Ant::disposeJsonNode(schema);
}
int Account::isEqualScheme(const std::string &json) {
    Ant::JsonNode *schema = Ant::jsonNodeParse(json.c_str());
    Ant::JsonNode *dtoSchema = Account::toJsonScheme();
    int result = Ant::jsonIsEqualScheme(dtoSchema, schema);
    Ant::disposeJsonNode(dtoSchema);
    Ant::disposeJsonNode(schema);
    return result;
}
