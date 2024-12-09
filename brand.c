#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "brand.h"

Brand* createBrand(const char* name) {
    Brand* brand = (Brand*)malloc(sizeof(Brand));
    if (brand) {
        brand->name = (char*)malloc((strlen(name) + 1) * sizeof(char)); 
        if (!brand->name) {
            fprintf(stderr, "Error: Memory allocation failed for brand name\n");
            free(brand); 
            return NULL;
        }
        strcpy(brand->name, name); 

        brand->products = NULL; 
        brand->productCount = 0;
    }
    return brand;
}

void deleteBrand(Brand* brand) {
    if (brand) {
        free(brand->name); 
        for (int i = 0; i < brand->productCount; i++) {
            free(brand->products[i]->description);
            free(brand->products[i]); 
        }
        free(brand->products); 
        free(brand); 
    }
}

void addProductToBrand(Brand* brand, Product* product) {
    if (!brand || !product) {
        fprintf(stderr, "Error: Brand or Product is NULL.\n");
        return;
    }

    Product** temp = (Product**)realloc(brand->products, (brand->productCount + 1) * sizeof(Product*));
    if (!temp) {
        fprintf(stderr, "Error: Memory reallocation failed for adding product to brand.\n");
        return;
    }

    brand->products = temp;
    brand->products[brand->productCount] = product;
    brand->productCount++;
}
void printBrand(Brand* brand) {
    if (brand) {
        printf("Brand: %s\n", brand->name);
        printf("  Products:\n");
        for (int i = 0; i < brand->productCount; i++) {
            printf("  %d. %s ", i + 1, brand->products[i]->name);
        }
    }
}
void printBrandName(Brand* brand) {
    if (brand) {
        printf("Brand: %s\n", brand->name);
    }
}

void freeBrand(Brand* brand) {
    deleteBrand(brand); 
}
