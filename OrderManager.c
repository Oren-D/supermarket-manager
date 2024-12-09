#include <stdio.h>
#include <stdlib.h>
#include "exe.h"

OrderManager* createOrderManager() {
    OrderManager* manager = (OrderManager*)malloc(sizeof(OrderManager));
    if (manager) {
        manager->head = NULL;
        manager->size = 0;
    }
    return manager;
}

void addOrder(OrderManager* manager, Order* newOrder) {
    if (!manager || !newOrder) return;

    OrderNode* newNode = (OrderNode*)malloc(sizeof(OrderNode));
    if (!newNode) return;

    newNode->data = newOrder;
    newNode->next = NULL;

    if (manager->head == NULL) {
        manager->head = newNode;
    }
    else {
        OrderNode* current = manager->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    manager->size++;
}
Order* findOrder(OrderManager* manager, int orderID) {
    if (!manager) return NULL;

    OrderNode* current = manager->head;
    while (current) {
        if (current->data->orderID == orderID) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

void deleteOrder(OrderManager* manager, int orderID) {
    if (!manager) return;

    OrderNode* current = manager->head;
    OrderNode* previous = NULL;

    while (current) {
        if (current->data->orderID == orderID) {
            if (previous) {
                previous->next = current->next;
            }
            else {
                manager->head = current->next;
            }
            freeOrder(current->data);
            free(current);
            manager->size--;
            return;
        }
        previous = current;
        current = current->next;
    }
}

void printOrderManager(OrderManager* manager) {
    if (!manager) return;

    OrderNode* current = manager->head;
    int i = 1;
    while (current) {
        printf("%d. ", i);
        printOrder(current->data);
        current = current->next;
    }
}

void freeOrderManager(OrderManager* manager) {
    if (!manager) return;

    OrderNode* current = manager->head;
    while (current) {
        OrderNode* next = current->next;
        freeOrder(current->data);
        free(current);
        current = next;
    }
    free(manager);
}

int isProductInAnyOrder(OrderManager* orderManager, Product* product) {
    if (!orderManager || !product) return -1;

    OrderNode* current = orderManager->head;
    while (current) {
        for (int i = 0; i < current->data->numOfProducts; i++) {
            if (current->data->orderedProducts[i] == product) {
                return 1; 
            }
        }
        current = current->next;
    }
    return -1; 
}

int isCategoryInAnyOrder(OrderManager* orderManager, const char* categoryName) {
    if (!orderManager || !categoryName) return -1;

    OrderNode* current = orderManager->head;
    while (current) {
        for (int i = 0; i < current->data->numOfProducts; i++) {
            if (strcmp(current->data->orderedProducts[i]->categoryName, categoryName) == 0) {
                return 1; 
            }
        }
        current = current->next;
    }
    return -1; 
}

int isBrandInAnyOrder(OrderManager* orderManager, const char* brandName) {
    if (!orderManager || !brandName) return -1;

    OrderNode* current = orderManager->head;
    while (current) {
        for (int i = 0; i < current->data->numOfProducts; i++) {
            if (strcmp(current->data->orderedProducts[i]->brandName, brandName) == 0) {
                return 1; 
            }
        }
        current = current->next;
    }
    return -1; 
}

int isSupplierInAnyOrder(OrderManager* orderManager, const char* supplierName) {
    if (!orderManager || !supplierName) return -1;

    OrderNode* current = orderManager->head;
    while (current) {
        for (int i = 0; i < current->data->numOfProducts; i++) {
            if (strcmp(current->data->orderedProducts[i]->supplierName, supplierName) == 0) {
                return 1; 
            }
        }
        current = current->next;
    }
    return -1; 
}

int isCustomerInAnyOrder(OrderManager* orderManager, Customer* customer) {
    if (!orderManager || !customer) return -1;

    OrderNode* current = orderManager->head;
    while (current) {
        if (current->data->customer == customer) {
            return 1;
        }
        current = current->next;
    }
    return -1; 
}
void addProductToOrder(Order* order, Product* product) {
    if (!order || !product) {
        return;
    }
    Product** temp = realloc(order->orderedProducts, (order->numOfProducts + 1) * sizeof(Product*));
    if (!temp) {
        fprintf(stderr, "Memory allocation failed when adding product to order.\n");
        return;
    }
    order->orderedProducts = temp;
    order->orderedProducts[order->numOfProducts] = product;
    order->numOfProducts++;
}