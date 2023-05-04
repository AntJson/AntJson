#include "json.h"
#include <stdlib.h>
#include <stdio.h>

int nodeNesting() {
    const char* key = "key";
    int intNum = 5;
    double doubleNum = 1.3;
    const char* charVal = "huipopa";
    JsonNode* node = (JsonNode*)malloc(sizeof(JsonNode));


    const char* newKey = "key2";
    JsonNode* newNode = (JsonNode*)malloc(sizeof(JsonNode));
    jsonAddField(newNode, number_i, newKey, &intNum);
    jsonAddField(node, object, key, newNode);

    printf("Nested node int value: %d\n", node->data->value->i);

    return 0;
}

void simpleEquality() {
    JsonNode* node1 = (JsonNode*)malloc(sizeof(JsonNode));
    JsonNode* node2 = (JsonNode*)malloc(sizeof(JsonNode));

    const char* key = "number";
    const char* key2 = "number";
    const char* number = "+7 (995) 911-09-53";
    jsonAddField(node1, string, key, number);
    jsonAddField(node2, string, key2, number);

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

    jsonAddField(node1, object, nodeKey, node1_1);
    jsonAddField(node1_1, string, key, number);

    JsonNode* node2 = (JsonNode*)malloc(sizeof(JsonNode));
    JsonNode* node2_1 = (JsonNode*)malloc(sizeof(JsonNode));
    jsonAddField(node2, object, nodeKey, node2_1);
    jsonAddField(node2_1, string, key2, number);


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

int main() {
    printf("\nSimple equality: \n");
    simpleEquality();
    printf("\nNested equality: \n");
    nestedEquality();
}