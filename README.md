# AntJson — Pretty way to manage DTOs in C/C++

As an example of JSON that will come from the client we'll use this one:
```json
{
  "account": {
    "password": "oo2929212____",
    "username": "Alex"
  },
  "ip":"109.18.2.100",
  "name":"nvr4ik",
  "port":37777
}
```

### How will it look:
##### C++:
> Note: this member-like style will work if defined `ANT_JSON_MEMBER` at the top of file that includes `antjson.h` or one-time defile in `antjson.h`. 
> If it's not defined see **C lang** part

###### Account DTO:
```c++
// account.h
struct Account {
    char* username;
    char* password;

    // Needed declaration for macro usage
    static int fromJson(AntJson::JsonNode *source, Account *dest);
    static AntJson::JsonNode *toJsonScheme();
};
...
// account.cpp
#include "account.h"
#include "antjson.h"

// Main macro for constructor
AntJson(Account,
    // Macro for member type if it's primitive and not object
    AntValue("username", username, s, AntJson::JsonNodeType::String)
    AntValue("password", password, s, AntJson::JsonNodeType::String)
)
```

###### NVR DTO:
> NVR DTO includes Account
```c++
// nvr.h
struct NVR {
    char* ip;
    char* name;
    int port;
    Account* account;

    // Needed declaration for macro usage
    static int fromJson(AntJson::JsonNode* source, NVR* dest);
    static AntJson::JsonNode* toJsonScheme();
};
...
// nvr.cpp
#include "nvr.h"
#include "antjson.h"

// Main macro for constructor
AntJson(NVR,
    // Macro for member type if it's primitive and not object
    AntValue("ip", ip, s, AntJson::JsonNodeType::String)
    AntValue("name", name, s, AntJson::JsonNodeType::String)
    AntValue("port", port, i, AntJson::JsonNodeType::Int)
    // Macro for member type if it's sub-struct
    AntStruct("account", account, Account)
)
```

###### Usage:
```c++
void parser(const char* json) {
    NVR nvr;
    // Parse scheme with meta from given JSON
    AntJson::JsonNode* jsonScheme = AntJson::jsonNodeParse(json);
    // Get JSON schema from DTO that we need to parse in
    AntJson::JsonNode* dtoScheme = NVR::toJsonScheme();
    // When we have both schemas we can compare them
    if (AntJson::jsonIsEqualScheme(jsonScheme, dtoScheme)) {
        // If schemas are equals we can parse it now and be sure
        // that parsing will be successful
        NVR::fromJson(jsonScheme, &nvr);
    } else {
        // If schemas are different throw error
        throw;
    }
    
}
```
