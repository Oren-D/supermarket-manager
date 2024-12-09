#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include "order.h"

typedef struct OrderNode {
    Order* data;
    struct OrderNode* next;
} OrderNode;

typedef struct {
    OrderNode* head;
    int size;
} OrderManager;
OrderManager* createOrderManager();
void addOrder(OrderManager* list, Order* newOrder);
Order* findOrder(OrderManager* list, int orderID);
void deleteOrder(OrderManager* list, int orderID);
void printOrderManager(OrderManager* list);
void freeOrderManager(OrderManager* list);
int isProductInAnyOrder(OrderManager* orderManager, Product* product);
int isCategoryInAnyOrder(OrderManager* orderManager, const char* categoryName);
int isBrandInAnyOrder(OrderManager* orderManager, const char* brandName);
int isSupplierInAnyOrder(OrderManager* orderManager, const char* supplierName);
int isCustomerInAnyOrder(OrderManager* orderManager, Customer* customer);
void addProductToOrder(Order* order, Product* product);



#endif // ORDER_MANAGER_H
