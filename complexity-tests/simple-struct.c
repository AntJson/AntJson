//
// Created by danysmall on 5/6/23.
//

#include "simple-struct.h"

DTOConstructor(
        PersonalData,
        DTOFieldConstructor("first_name", firstName, s)
        DTOFieldConstructor("last_name", lastName, s)
)

JsonNode* getPersonalDataJson() {
//    Create root node
    JsonNode* rootNode = getEmptyJsonNode("", object);

//    Create first name node
    JsonNode* firstNameNode = getEmptyJsonNode("first_name", string);
    firstNameNode->value.s = "Daniel";

//    Create last name node
    JsonNode* lastNameNode = getEmptyJsonNode("last_name", string);
    lastNameNode->value.s = "Smolyakov";

//    Add children nodes to root node
    addChild(rootNode, firstNameNode);
    addChild(rootNode, lastNameNode);
    return rootNode;
}

void printPersonalData(PersonalData personalData) {
    printf("First name: %s\n", personalData.firstName);
    printf("Last name: %s\n", personalData.lastName);
}

void testPersonalData() {
    PersonalData* personalData = (PersonalData*) malloc(sizeof(PersonalData));
    JsonNode* personalDataJson = getPersonalDataJson();
    __constructor__PersonalData(personalDataJson, personalData);
    printPersonalData(*personalData);
}