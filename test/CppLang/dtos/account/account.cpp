#include "account.h"

AntJson(
        Account,
        AntValue("username", username, AntString)
        AntValue("password", password, AntString)
)