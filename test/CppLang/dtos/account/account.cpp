#include "account.h"

AntJson(Account,
    // Macro for member type if it's primitive and not object
    AntValue("username", username, AntString)
    AntValue("password", password, AntString)
)