#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

Customer* createCustomer(const char* name, const char* email, int customerID, Address* address) {
    Customer* customer = (Customer*)malloc(sizeof(Customer));
    if (!customer) {
        fprintf(stderr, "Error: Memory allocation failed for Customer\n");
        return NULL;
    }

    customer->name = (char*)malloc(strlen(name) + 1); 
    if (!customer->name) {
        fprintf(stderr, "Error: Memory allocation failed for customer name\n");
        free(customer); 
        return NULL;
    }
    strcpy(customer->name, name);

    if (!customer->email) {
        fprintf(stderr, "Error: Memory allocation failed for customer email\n");
        free(customer->name);
        free(customer); 
        return NULL;
    }
    strcpy(customer->email, email);

    customer->customerID = customerID;
    customer->address = (Address*)malloc(sizeof(Address));
    if (customer->address == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for customer address\n");
        return NULL;
    }
    *(customer->address) = *address;
    customer->address = address; 

    return customer;
}void updateCustomer(Customer* customer, const char* name, const char* email, Address* address) {
    if (customer) {
        free(customer->name);
        strcpy(customer->name,name);
        strcpy(customer->email, email);
        customer->address = address;
    }
}

void printCustomer(Customer* customer) {
    if (customer) {
        printf("Customer ID: %d\n", customer->customerID);
        printf("Name: %s\n", customer->name);
        printf("Email: %s\n", customer->email);
    }
}

void freeCustomer(Customer* customer) {
    if (customer) {
        free(customer->name); 
        free(customer); 
    }
}
