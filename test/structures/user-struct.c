//
// Created by danysmall on 5/11/23.
//

#include "user-struct.h"
#include "../../macro/macro.h"

DTOConstructor(User,
        DTOFieldConstructor("age", age, i, number_i)
        DTOStructConstructor("profile", profile, Profile))