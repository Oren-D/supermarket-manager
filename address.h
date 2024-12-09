#ifndef ADDRESS_H
#define ADDRESS_H

typedef struct {
    char street[100];
    char city[50];
    int postalCode;
} Address;

Address* createAddress(const char* street, const char* city, int postalCode);
void updateAddress(Address* address, const char* street, const char* city, int postalCode);
void printAddress(Address* address);
void freeAddress(Address* address);

#endif // ADDRESS_H
