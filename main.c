#include "complexity-tests/nested-structs.h"
#include "complexity-tests/simple-struct.h"
#include "json-parser/json-token-test.h"
#include "json-parser/tokenizer/tokenizer.h"

const char* json = "{"
                   "\"key\": {"
                   "\"second_key\":\"value\""
                   "}"
                   "}";

const char* json2 = "{\"key\":{\"second_key\":{\"third_key\":\"value\"}}}";

int main() {
//    testPersonalData();
//    testPhoneNumber();
//    __testJsonToken();
    jsonTokenFromJsonString((char*)json2);
}