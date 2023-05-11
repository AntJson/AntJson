//
// Created by danysmall on 5/11/23.
//

#include "contacts-struct.h"
#include "../../../json-node/json.h"

#ifndef DTOCONSTRUCTOR_PROFILE_STRUCT_H
#define DTOCONSTRUCTOR_PROFILE_STRUCT_H

typedef struct {
    int married;
    Contacts* contacts;
} Profile;

int ProfileFromJson(JsonNode* node, Profile* dest);
JsonNode* ProfileToJsonScheme();

#endif //DTOCONSTRUCTOR_PROFILE_STRUCT_H
