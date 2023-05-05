#include "json.h"
#include "json-macro.h"
#include <stdlib.h>
#include <stdio.h>

/*
int nodeNesting() {
    const char* key = "key";
    int intNum = 5;
    double doubleNum = 1.3;
    const char* charVal = "huipopa";
    JsonNode* node = (JsonNode*)malloc(sizeof(JsonNode));


    const char* newKey = "key2";
    JsonNode* newNode = (JsonNode*)malloc(sizeof(JsonNode));
    updateNode(newNode, number_i, newKey, &intNum);
    updateNode(node, object, key, newNode);

    printf("Nested node int value: %d\n", node->value->i);

    return 0;
}

void simpleEquality() {
    JsonNode* node1 = (JsonNode*)malloc(sizeof(JsonNode));
    JsonNode* node2 = (JsonNode*)malloc(sizeof(JsonNode));

    const char* key = "number";
    const char* key2 = "number";
    const char* number = "+7 (995) 911-09-53";
    updateNode(node1, string, key, number);
    updateNode(node2, string, key2, number);

    if (jsonIsEqualScheme(node1, node2)) {
        printf("Equals\n");
    } else {
        printf("Not equals\n");
    }

    free(node1);
    free(node2);
    return 0;
}

void nestedEquality() {
    const char* nodeKey = "node";
    const char* key = "number";
    const char* key2 = "number2";
    const char* number = "+7 (995) 911-09-53";

    JsonNode* node1 = (JsonNode*)malloc(sizeof(JsonNode));
    JsonNode* node1_1 = (JsonNode*)malloc(sizeof(JsonNode));

    updateNode(node1, object, nodeKey, node1_1);
    updateNode(node1_1, string, key, number);

    JsonNode* node2 = (JsonNode*)malloc(sizeof(JsonNode));
    JsonNode* node2_1 = (JsonNode*)malloc(sizeof(JsonNode));
    updateNode(node2, object, nodeKey, node2_1);
    updateNode(node2_1, string, key2, number);


    if (jsonIsEqualScheme(node1, node2)) {
        printf("Equals\n");
    } else {
        printf("Not equals\n");
    }

    free(node1);
    free(node1_1);
    free(node2);
    free(node2_1);
}

void testMacross() {
    const char* name = "Dany";
    int error = 0;
    char* temp;

    A* source = (A*)malloc(sizeof(A));
    
    error = __set__A__firstName(source, "some-key", name);
    if (!error) {
        printf("Cannot set name\n");
    }

    error = __set__A__firstName(source, "first_name", name);
    if (!error) {
        printf("Cannot set name\n");
    }

    temp = __get__A__firstName(source);
    printf("First name: %s\n", temp);
}
*/

JsonNode* getNode() {
    JsonNode* parent = (JsonNode*)malloc(sizeof(JsonNode));
    parent->type = object;
    parent->key = "";
    parent->childrenLength = 0;
    parent->children = (JsonNode**)malloc(0);

    JsonNode* number = (JsonNode*)malloc(sizeof(JsonNode));
    JsonNode* firstName = (JsonNode*)malloc(sizeof(JsonNode));
    JsonNode* lastName = (JsonNode*)malloc(sizeof(JsonNode));

    number->type = number_i;
    number->key = "phone_number";
    number->value.i = 999;

    firstName->type = string;
    firstName->key = "first_name";
    firstName->value.s = "Daniel";

    lastName->type = string;
    lastName->key = "last_name";
    lastName->value.s = "Smolyakov";

    // Add child nodes to parent
    addChild(parent, number);
    addChild(parent, firstName);
    addChild(parent, lastName);
}

typedef struct {
    int number;
    char* firstName;
    char* lastName;
} SomeDTO;
DTOConstructor(
    SomeDTO,
    DTOFieldConstructor("phone_number", number, i)
    DTOFieldConstructor("first_name", firstName, s)
    DTOFieldConstructor("last_name", lastName, s)
)


int main() {
    JsonNode* jsonData = getNode();
    SomeDTO* dto = (SomeDTO*)malloc(sizeof(SomeDTO));
    __constructor__SomeDTO(jsonData, dto);

    printf("Number: %d\n", dto->number);
    printf("FirstName: %s\n", dto->firstName);
    printf("LastName: %s\n", dto->lastName);
}