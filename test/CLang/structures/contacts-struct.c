//
// Created by danysmall on 5/11/23.
//

#include "contacts-struct.h"
#include "../../../macro/macro-c.h"

DTOConstructor(Contacts,
        DTOFieldConstructor("number", number, s, JsonNodeTypeString))