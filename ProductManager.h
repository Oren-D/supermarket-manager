#ifndef PRODUCT_MANAGER_H
#define PRODUCT_MANAGER_H

#include "product.h"
#include "commonFunctions.h" // Assuming this header contains iterateOverArray

typedef struct {
    Product** products;
    int productCount;
} ProductManager;

ProductManager* createProductManager();
void addProductToManager(ProductManager* manager, Product* newProduct);
Product* findProductInManager(ProductManager* manager, int productID);
void updateProductInManager(ProductManager* manager, int productID, const char* name, const char* description, double price, Date manufactureDate);
void deleteProductFromManager(ProductManager* manager, int productID);
void printProductManager(ProductManager* manager);
void printShortProductManager(ProductManager* manager);
void freeProductManager(ProductManager* manager);
void freeProductAction(void* product);
void printShortProductAction(void* product);

#endif // PRODUCT_MANAGER_H
