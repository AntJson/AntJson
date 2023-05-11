//
// Created by danysmall on 5/11/23.
//

#include "../../../json-node/json.h"

#ifndef DTOCONSTRUCTOR_CONTACTS_STRUCT_H
#define DTOCONSTRUCTOR_CONTACTS_STRUCT_H

typedef struct {
    char* number;
} Contacts;

int ContactsFromJson(JsonNode* node, Contacts* dest);
JsonNode* ContactsToJsonScheme();

#endif //DTOCONSTRUCTOR_CONTACTS_STRUCT_H
