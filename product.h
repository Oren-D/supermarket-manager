#ifndef PRODUCT_H
#define PRODUCT_H

#include "date.h"

typedef struct {
    char name[50];
    char* description;
    int productID;
    double price;
    Date manufactureDate;
    char* brandName;      
    char* categoryName;   
    char* supplierName;   
} Product;

Product* createProduct(const char* name, const char* description, int productID, double price, Date manufactureDate, const char* brandName, const char* categoryName, const char* supplierName);
void updateProduct(Product* product, const char* name, const char* description, double price, Date manufactureDate, const char* brandName, const char* categoryName, const char* supplierName);
void printProduct(Product* product);
void freeProduct(Product* product);

#endif // PRODUCT_H
