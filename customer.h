#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "address.h"

typedef struct Customer {
    char* name;
    char email[100];
    int customerID;
    Address* address;
} Customer;

Customer* createCustomer(const char* name, const char* email, int customerID, Address* address);
void updateCustomer(Customer* customer, const char* name, const char* email, Address* address);
void printCustomer(Customer* customer);
void freeCustomer(Customer* customer);

#endif // CUSTOMER_H
