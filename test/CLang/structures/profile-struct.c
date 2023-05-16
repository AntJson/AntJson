//
// Created by danysmall on 5/11/23.
//

#include "profile-struct.h"
#include "../../../macro/macro-c.h"

DTOConstructor(Profile,
        DTOFieldConstructor("married", married, b, JsonNodeTypeBool)
        DTOStructConstructor("contacts", contacts, Contacts))