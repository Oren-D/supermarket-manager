#include <stdio.h>
#include <stdlib.h>
#include "exe.h"

CustomerManager* createCustomerManager() {
    CustomerManager* manager = (CustomerManager*)malloc(sizeof(CustomerManager));
    if (manager) {
        manager->head = NULL;
        manager->tail = NULL;
    }
    return manager;
}

void addCustomer(CustomerManager* manager, Customer* newCustomer) {
    if (!manager || !newCustomer) return;

    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
    if (!newNode) return;

    newNode->data = newCustomer;
    newNode->next = NULL;
    newNode->prev = manager->tail;

    if (manager->tail) {
        manager->tail->next = newNode;
    }
    else {
        manager->head = newNode;
    }
    manager->tail = newNode;
}

Customer* findCustomer(CustomerManager* manager, int customerID) {
    if (!manager) return NULL;

    DListNode* current = manager->head;
    while (current) {
        if (current->data->customerID == customerID) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

void deleteCustomer(CustomerManager* manager, int customerID) {
    if (!manager) return;

    DListNode* current = manager->head;
    while (current) {
        if (current->data->customerID == customerID) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            else {
                manager->head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            }
            else {
                manager->tail = current->prev;
            }
            freeCustomer(current->data);
            free(current);
            return;
        }
        current = current->next;
    }
    printf("Customer with ID %d not found.\n", customerID);
}
void printCustomerManager(CustomerManager* manager) {
    if (!manager) {
        printf("Error: Customer manager is NULL.\n");
        return;
    }

    if (!manager->head) {
        printf("No customers available.\n");
        return;
    }

    DListNode* current = manager->head;
    int i = 1;

    printf("\n=== Customer List ===\n");
    while (current) {
        printf("\n%d. ", i);
        printCustomer(current->data);
        current = current->next;
        i++;
    }
    printf("\n=====================\n");
}

void freeCustomerManager(CustomerManager* manager) {
    if (!manager) return;

    DListNode* current = manager->head;
    while (current) {
        DListNode* next = current->next;
        freeCustomer(current->data);
        free(current);
        current = next;
    }

    free(manager);
}
void printShortCustomerManager(CustomerManager* customerManager) {
    if (!customerManager) {
        printf("Error: Customer manager is NULL\n");
        return;
    }

    DListNode* current = customerManager->head;
    printf("\n=== Existing Customers ===\n");
    while (current) {
        printf("ID: %d, Name: %s\n", current->data->customerID, current->data->name);
        current = current->next;
    }
    if (!customerManager->head) {
        printf("No customers found.\n");
    }
}
Customer* getCustomerByIndex(CustomerManager* customerManager, int index) {
    DListNode* current = customerManager->head;
    int currentIndex = 0;

    while (current != NULL && currentIndex < index) {
        current = current->next;
        currentIndex++;
    }

    if (current != NULL) {
        return current->data;
    }
    else {
        return NULL; // Index out of range
    }
}
Customer* findCustomerByName(CustomerManager* customerManager, const char* name) {
    if (!customerManager || !name) {
        return NULL;
    }

    DListNode* current = customerManager->head;
    while (current) {
        if (strcmp(current->data->name, name) == 0) {
            return current->data;
        }
        current = current->next;
    }

    return NULL;
}