#define _CRT_SECURE_NO_WARNINGS
#include "product.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Product* createProduct(const char* name, const char* description, int productID, double price, Date manufactureDate, const char* brandName, const char* categoryName, const char* supplierName) {
    Product* product = (Product*)malloc(sizeof(Product));
    if (product) {
        strncpy(product->name, name, sizeof(product->name) - 1);
        product->name[sizeof(product->name) - 1] = '\0';

        product->description = (char*)malloc(strlen(description) + 1);
        if (product->description) {
            strcpy(product->description, description);
        }

        product->productID = productID;
        product->price = price;
        product->manufactureDate = manufactureDate;

        product->brandName = (char*)malloc(strlen(brandName) + 1);
        if (product->brandName) {
            strcpy(product->brandName, brandName);
        }

        product->categoryName = (char*)malloc(strlen(categoryName) + 1);
        if (product->categoryName) {
            strcpy(product->categoryName, categoryName);
        }

        product->supplierName = (char*)malloc(strlen(supplierName) + 1);
        if (product->supplierName) {
            strcpy(product->supplierName, supplierName);
        }
    }
    return product;
}

void updateProduct(Product* product, const char* name, const char* description, double price, Date manufactureDate, const char* brandName, const char* categoryName, const char* supplierName) {
    if (product) {
        strncpy(product->name, name, sizeof(product->name) - 1);
        product->name[sizeof(product->name) - 1] = '\0';

        free(product->description);
        product->description = (char*)malloc(strlen(description) + 1);
        if (product->description) {
            strcpy(product->description, description);
        }

        product->price = price;
        product->manufactureDate = manufactureDate;

        free(product->brandName);
        product->brandName = (char*)malloc(strlen(brandName) + 1);
        if (product->brandName) {
            strcpy(product->brandName, brandName);
        }

        free(product->categoryName);
        product->categoryName = (char*)malloc(strlen(categoryName) + 1);
        if (product->categoryName) {
            strcpy(product->categoryName, categoryName);
        }

        free(product->supplierName);
        product->supplierName = (char*)malloc(strlen(supplierName) + 1);
        if (product->supplierName) {
            strcpy(product->supplierName, supplierName);
        }
    }
}

void printProduct(Product* product) {
    if (product) {
        printf("Product Name: %s\n", product->name);
        printf("Description: %s\n", product->description);
        printf("Product ID: %d\n", product->productID);
        printf("Price: %.2f\n", product->price);
        printf("Manufacture Date: %04d-%02d-%02d\n", product->manufactureDate.year, product->manufactureDate.month, product->manufactureDate.day);
        printf("Brand: %s\n", product->brandName);
        printf("Category: %s\n", product->categoryName);
        printf("Supplier: %s\n", product->supplierName);
    }
}

void freeProduct(Product* product) {
    if (product) {
        free(product->description);
        free(product->brandName);
        free(product->categoryName);
        free(product->supplierName);
        free(product);
    }
}
