//
// Created by danysmall on 5/6/23.
//
#ifndef NESTED_STRUCTS_H
#define NESTED_STRUCTS_H

#include "../json-node/json.h"
#include "../json-node/json-macro.h"

typedef struct {
    char* regionCode;
    char* countryCode;
} PhoneNumberMeta;

typedef struct {
    char* phoneNumber;
    PhoneNumberMeta* meta;
} PhoneNumber;

JsonNode* getPhoneNumberJson();
void printPhoneNumber(PhoneNumber phoneNumber);
void printPhoneNumberMeta(PhoneNumberMeta phoneNumberMeta);
void testPhoneNumber();

#endif // NESTED_STRUCTS_H
