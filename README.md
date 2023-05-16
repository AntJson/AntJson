# AntJson — Pretty way to manage DTOs in C/C++

## Last changes:
Removed double type definitions in macro decorators. Previously they were:
```c++
AntValue("username", username, s, Ant::JsonNodeType::String)
```
and now they look like:
```c++
AntValue("username", username, AntString)
```

Types mapping that have to be in `AntValue`:
| Macro definition | C | C++ |
| --- | --- | --- |
| AntString | String | Ant::JsonNodeType::String |
| AntInt | Int | Ant::JsonNodeType::Int |
| AntFloat | Float | Ant::JsonNodeType::Float |
| AntBool | Bool | Ant::JsonNodeType::Bool |


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
    static int fromJson(Ant::JsonNode *source, Account *dest);
    static Ant::JsonNode *toJsonScheme();
};
...
// account.cpp
#include "account.h"
#include "antjson.h"

// Main macro for constructor
AntJson(Account,
    // Macro for member type if it's primitive and not object
    AntValue("username", username, AntString)
    AntValue("password", password, AntString)
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
    Account account;
    std::vector<int> numbersArray;

    // Needed declaration for macro usage
    static int fromJson(Ant::JsonNode* source, NVR* dest);
    static Ant::JsonNode* toJsonScheme();
};
...
// nvr.cpp
#include "nvr.h"
#include "antjson.h"

// Main macro for constructor
AntJson(NVR,
    // Macro for member type if it's primitive and not object
    AntValue("ip", ip, AntString)
    AntValue("name", name, AntString)
    AntValue("port", port, AntInt)
    // Macro for member type if it's sub-struct
    AntStruct("account", account, Account)
    // Array definition
    AntValue("test", numbersArray, AntArray, AntInt)
)
```

###### Usage:
```c++
void parser(const char* json) {
    NVR nvr;
    // Parse scheme with meta from given JSON
    Ant::JsonNode* jsonScheme = Ant::jsonNodeParse(json);
    // Get JSON schema from DTO that we need to parse in
    Ant::JsonNode* dtoScheme = NVR::toJsonScheme();
    // When we have both schemas we can compare them
    if (Ant::jsonIsEqualScheme(jsonScheme, dtoScheme)) {
        // If schemas are equals we can parse it now and be sure
        // that parsing will be successful
        NVR::fromJson(jsonScheme, &nvr);
    } else {
        // If schemas are different throw error
        throw;
    }
    
}
```
