//
// Created by danysmall on 5/6/23.
//
#ifndef SIMPLE_STRUCT_H
#define SIMPLE_STRUCT_H

#include "../json-node/json.h"
#include "../json-node/json-macro.h"

typedef struct {
    char* firstName;
    char* lastName;
} PersonalData;

// Helper methods
JsonNode* getPersonalDataJson();
void printPersonalData(PersonalData personalData);
void testPersonalData();

#endif // SIMPLE_STRUCT_H
