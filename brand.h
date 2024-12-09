#ifndef BRAND_H
#define BRAND_H

#include "product.h"

typedef struct Brand {
    char* name;
    Product** products;
    int productCount;
} Brand;

Brand* createBrand(const char* name);
void deleteBrand(Brand* brand);
void addProductToBrand(Brand* brand, Product* product);
void printBrand(Brand* brand);
void freeBrand(Brand* brand);
void  printBrandName(Brand* brand);
#endif // BRAND_H
