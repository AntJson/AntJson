#include "complexity-tests/nested-structs.h"
#include "complexity-tests/simple-struct.h"
#include "json-parser/json-token-test.h"
#include "json-parser/tokenizer/tokenizer.h"

const char* json = "{"
                   "\"key\": {"
                   "\"second_key\":\"value\""
                   "}"
                   "}";

const char* json2 = "{\"key\":{\"second_key\":{\"third_key\":\"value\", \"fourth_key\":\"value_2\"}}}";

/**
{
  "1": "1.data",
  "2": {
    "2.1": "2.1.data",
    "2.2": "2.2.data"
  },
  "3": {
    "3.1": {
      "3.1.1": "3.1.1.data",
      "3.1.2": "3.1.2.data"
    },
    "3.2": "3.2.data"
  },
  "4": {
    "4.1": {
      "4.1.1": {
        "4.1.1.1": "4.1.1.1.data"
      }
    }
  }
}
 */
const char* complexJson = "{\n"
                          "  \"1\": \"1.data\",\n"
                          "  \"2\": {\n"
                          "    \"2.1\": \"2.1.data\",\n"
                          "    \"2.2\": \"2.2.data\"\n"
                          "  },\n"
                          "  \"3\": {\n"
                          "    \"3.1\": {\n"
                          "      \"3.1.1\": \"3.1.1.data\",\n"
                          "      \"3.1.2\": \"3.1.2.data\"\n"
                          "    },\n"
                          "    \"3.2\": \"3.2.data\"\n"
                          "  },\n"
                          "  \"4\": {\n"
                          "    \"4.1\": {\n"
                          "      \"4.1.1\": {\n"
                          "        \"4.1.1.1\": \"4.1.1.1.data\"\n"
                          "      }\n"
                          "    }\n"
                          "  }\n"
                          "}";

int main() {
//    testPersonalData();
//    testPhoneNumber();
//    __testJsonToken();
    jsonTokenFromJsonString((char*)complexJson);
}