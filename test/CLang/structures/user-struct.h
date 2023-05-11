//
// Created by danysmall on 5/11/23.
//
#include "profile-struct.h"
#include "../../../json-node/json.h"

#ifndef DTOCONSTRUCTOR_USER_STRUCT_H
#define DTOCONSTRUCTOR_USER_STRUCT_H

typedef struct {
    int age;
    Profile* profile;
} User;

int UserFromJson(JsonNode* node, User* dest);
JsonNode* UserToJsonScheme();

#endif //DTOCONSTRUCTOR_USER_STRUCT_H
