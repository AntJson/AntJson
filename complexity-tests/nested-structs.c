//
// Created by danysmall on 5/6/23.
//

#include "nested-structs.h"

DTOConstructor(
    PhoneNumberMeta,
    DTOFieldConstructor("region_code", regionCode, s)
    DTOFieldConstructor("country_code", countryCode, s)
)

DTOConstructor(
    PhoneNumber,
    DTOFieldConstructor("phone_number", phoneNumber, s)
    DTOStructConstructor("meta", meta, PhoneNumberMeta)
)

JsonNode* getPhoneNumberJson() {
//    Create root node
    JsonNode* rootNode = getEmptyJsonNode("", object);

//    Create phone number node
    JsonNode* phoneNumber = getEmptyJsonNode("phone_number", string);
    phoneNumber->value.s = "+7 (999) 999-00-01";

//    Create meta root node (as JSON object that contains elements)
    JsonNode* phoneNumberMetaRoot = getEmptyJsonNode("meta", object);

//    Create meta child nodes
    JsonNode* countryCode = getEmptyJsonNode("country_code", string);
    countryCode->value.s = "RU";

    JsonNode* regionCode = getEmptyJsonNode("region_code", string);
    regionCode->value.s = "+7";

//    Add meta nodes to meta root
    addChild(phoneNumberMetaRoot, countryCode);
    addChild(phoneNumberMetaRoot, regionCode);

//    Add meta root to main root
    addChild(rootNode, phoneNumberMetaRoot);
//    Add phone number to main root
    addChild(rootNode, phoneNumber);

    return rootNode;
}

void printPhoneNumber(PhoneNumber phoneNumber) {
    printf("Phone number: %s\n", phoneNumber.phoneNumber);
    printPhoneNumberMeta(*phoneNumber.meta);
}

void printPhoneNumberMeta(PhoneNumberMeta phoneNumberMeta) {
    printf("Country code: %s\n", phoneNumberMeta.countryCode);
    printf("Region code: %s\n", phoneNumberMeta.regionCode);
}

void testPhoneNumber() {
    JsonNode* phoneNumberJson = getPhoneNumberJson();

    PhoneNumber* phoneNumber = (PhoneNumber*) malloc(sizeof(PhoneNumber));
    PhoneNumberMeta* phoneNumberMeta = (PhoneNumberMeta*)malloc(sizeof(PhoneNumberMeta));
    phoneNumber->meta = phoneNumberMeta;

    __constructor__PhoneNumber(phoneNumberJson, phoneNumber);
    printPhoneNumber(*phoneNumber);
}