#include "nvr.h"

AntJson(NVR,
    // Macro for member type if it's primitive and not object
    AntValue("ip", ip, AntString)
    AntValue("name", name, AntString)
    AntValue("port", port, AntInt)
    AntValue("numbersArray", numbersArray, AntArray, AntInt)
    // Array with struct template type
    AntStructArray("accountArray", accountArray, Account)
    // Macro for member type if it's sub-struct
    AntStruct("account", account, Account)
)