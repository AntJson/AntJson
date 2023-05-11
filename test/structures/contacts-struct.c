//
// Created by danysmall on 5/11/23.
//

#include "contacts-struct.h"
#include "../../macro/macro.h"

DTOConstructor(Contacts,
        DTOFieldConstructor("number", number, s, string))