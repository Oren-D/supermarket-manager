#ifndef CATEGORY_H
#define CATEGORY_H

#include "product.h"

typedef struct {
    char name[50];
    Product** products;
    int productCount;
} Category;

Category* createCategory(const char* name);
void addProductToCategory(Category* category, Product* product);
void updateCategory(Category* category, const char* name);
void printCategory(Category* category);
void printCategoryName(Category* category);
void freeCategory(Category* category);

#endif // CATEGORY_H
