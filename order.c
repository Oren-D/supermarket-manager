#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "order.h"

Order* createOrder(int orderID, Customer* customer, Date orderDate) {
    Order* order = (Order*)malloc(sizeof(Order));
    if (order) {
        order->orderID = orderID;
        order->customer = customer;
        order->orderedProducts = NULL;
        order->numOfProducts = 0;
        order->orderDate = orderDate;
    }
    return order;
}

void updateOrder(Order* order, Customer* customer, Date orderDate) {
    if (order) {
        order->customer = customer;
        order->orderDate = orderDate;
    }
}

void printOrder(Order* order) {
    if (order) {
        printf("Order ID: %d\n", order->orderID);
        printf("Customer Name: %s\n", order->customer->name);
        printf("Order Date: %04d-%02d-%02d\n", order->orderDate.year, order->orderDate.month, order->orderDate.day);

        if (order->numOfProducts > 0 && order->orderedProducts) {
            printf("Products in this order:\n");
            for (int i = 0; i < order->numOfProducts; i++) {
                if (order->orderedProducts[i]) {
                    printProduct(order->orderedProducts[i]);
                    printf("\n");
                }
            }
        }
        else {
            printf("No products in this order.\n");
        }
    }
    else {
        printf("Invalid order.\n");
    }
}

void freeOrder(Order* order) {
    if (order) {
        for (int i = 0; i < order->numOfProducts; i++) {
            free(order->orderedProducts[i]->description); 
            free(order->orderedProducts[i]);      
        }
        free(order->orderedProducts); 
        free(order);                
    }
}
