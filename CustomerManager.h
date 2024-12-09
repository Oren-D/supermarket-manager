#ifndef CUSTOMER_MANAGER_H
#define CUSTOMER_MANAGER_H

#include "customer.h"

typedef struct DListNode {
    Customer* data;
    struct DListNode* next;
    struct DListNode* prev;
} DListNode;

typedef struct {
    DListNode* head;
    DListNode* tail;
} CustomerManager;
void printShortCustomerManager(CustomerManager* customerManager);
CustomerManager* createCustomerManager();
void addCustomer(CustomerManager* list, Customer* newCustomer);
Customer* findCustomer(CustomerManager* list, int customerID);
void deleteCustomer(CustomerManager* list, int customerID);
void printCustomerManager(CustomerManager* list);
void freeCustomerManager(CustomerManager* list);
Customer* getCustomerByIndex(CustomerManager* customerManager, int index);
Customer* findCustomerByName(CustomerManager* customerManager, const char* name);

#endif // CUSTOMER_MANAGER_H
