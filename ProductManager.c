#include "productManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
ProductManager* createProductManager() {
    ProductManager* manager = (ProductManager*)malloc(sizeof(ProductManager));
    if (manager) {
        manager->products = NULL;
        manager->productCount = 0;
    }
    return manager;
}
void addProductToManager(ProductManager* manager, Product* newProduct) {
    if (!manager || !newProduct) return;

    manager->products = (Product**)realloc(manager->products, (manager->productCount + 1) * sizeof(Product*));
    if (!manager->products) {
        fprintf(stderr, "Error: Memory allocation failed for products array\n");
        return;
    }

    manager->products[manager->productCount] = newProduct;
    manager->productCount++;
}
Product* findProductInManager(ProductManager* manager, int productID) {
    if (!manager) return NULL;

    for (int i = 0; i < manager->productCount; i++) {
        if (manager->products[i]->productID == productID) {
            return manager->products[i];
        }
    }
    return NULL;
}
void updateProductInManager(ProductManager* manager, int productID, const char* name, const char* description, double price, Date manufactureDate) {
    Product* product = findProductInManager(manager, productID);
    if (product) {
        updateProduct(product, name, description, price, manufactureDate, product->brandName, product->categoryName, product->supplierName);
    }
    else {
        printf("Product with ID %d not found.\n", productID);
    }
}
void deleteProductFromManager(ProductManager* manager, int productID) {
    if (!manager) return;

    for (int i = 0; i < manager->productCount; i++) {
        if (manager->products[i]->productID == productID) {
            freeProduct(manager->products[i]);

            for (int j = i; j < manager->productCount - 1; j++) {
                manager->products[j] = manager->products[j + 1];
            }

            manager->products = (Product**)realloc(manager->products, (manager->productCount - 1) * sizeof(Product*));
            manager->productCount--;
            return;
        }
    }

    printf("Product with ID %d not found.\n", productID);
}
void printProductAction(void* product) {
    printProduct((Product*)product);
}
void printProductManager(ProductManager* manager) {
    if (!manager) return;

    if (manager->productCount == 0) {
        printf("No products available.\n");
        return;
    }

    printf("\n=== Products List ===\n");
    iterateOverArray((void**)manager->products, manager->productCount, printProductAction);
}

void printShortProductAction(void* product) {
    Product* prod = (Product*)product;
    printf("ID: %d, Name: %s\n", prod->productID, prod->name);
}
void printShortProductManager(ProductManager* productManager) {
    if (!productManager) {
        printf("Error: Product manager is NULL\n");
        return;
    }

    printf("\n=== Existing Products ===\n");
    iterateOverArray((void**)productManager->products, productManager->productCount, printShortProductAction);

    if (productManager->productCount == 0) {
        printf("No products found.\n");
    }
}
void freeProductAction(void* product) {
    freeProduct((Product*)product);
}

void freeProductManager(ProductManager* manager) {
    if (!manager) return;

    iterateOverArray((void**)manager->products, manager->productCount, freeProductAction);

    free(manager->products);
    free(manager);
}
