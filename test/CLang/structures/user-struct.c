//
// Created by danysmall on 5/11/23.
//

#include "user-struct.h"
#include "../../../macro/macro-c.h"

DTOConstructor(User,
        DTOFieldConstructor("age", age, i, JsonNodeTypeInt)
        DTOStructConstructor("profile", profile, Profile))