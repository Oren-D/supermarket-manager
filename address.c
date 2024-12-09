#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "address.h"

Address* createAddress(const char* street, const char* city, int postalCode) {
    Address* address = (Address*)malloc(sizeof(Address));
    if (!address) {
        fprintf(stderr, "Error: Memory allocation failed for Address\n");
        return NULL;
    }

    strncpy(address->street, street, sizeof(address->street) - 1);
    address->street[sizeof(address->street) - 1] = '\0';

    strncpy(address->city, city, sizeof(address->city) - 1);
    address->city[sizeof(address->city) - 1] = '\0';

    address->postalCode = postalCode;

    return address;
}

void updateAddress(Address* address, const char* street, const char* city, int postalCode) {
    if (address) {
        strncpy(address->street, street, sizeof(address->street) - 1);
        address->street[sizeof(address->street) - 1] = '\0'; 
        strncpy(address->city, city, sizeof(address->city) - 1);
        address->city[sizeof(address->city) - 1] = '\0'; 
        address->postalCode = postalCode;
    }
}

void printAddress(Address* address) {
    if (address) {
        printf("Street: %s\n", address->street);
        printf("City: %s\n", address->city);
        printf("Postal Code: %d\n", address->postalCode);
    }
}

void freeAddress(Address* address) {
    if (address) {
        free(address);
    }
}
