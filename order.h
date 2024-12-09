#ifndef ORDER_H
#define ORDER_H

#include "product.h"
#include "customer.h"
#include "date.h"

typedef struct {
    int orderID;
    Customer* customer;
    Product** orderedProducts;
    int numOfProducts;
    Date orderDate;
} Order;



Order* createOrder(int orderID, Customer* customer, Date orderDate);
void updateOrder(Order* order, Customer* customer, Date orderDate);
void printOrder(Order* order);
void freeOrder(Order* order);


#endif // ORDER_H
