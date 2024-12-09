#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "category.h"

Category* createCategory(const char* name) {
    Category* category = (Category*)malloc(sizeof(Category));
    if (category) {
        strncpy(category->name, name, sizeof(category->name) - 1);
        category->name[sizeof(category->name) - 1] = '\0';
        category->products = NULL; 
        category->productCount = 0;
    }
    return category;
}

void addProductToCategory(Category* category, Product* product) {
    if (!category || !product) {
        fprintf(stderr, "Error: Category or Product is NULL.\n");
        return;
    }
    if (category->products == NULL) {
        category->products = (Product**)malloc(sizeof(Product*));
        if (!category->products) {
            fprintf(stderr, "Error: Memory allocation failed for products array.\n");
            return;
        }
        category->productCount = 0;
    }
    else {
        Product** temp = (Product**)realloc(category->products, (category->productCount + 1) * sizeof(Product*));
        if (!temp) {
            fprintf(stderr, "Error: Memory reallocation failed for adding product to category.\n");
            return;
        }
        category->products = temp;
    }

    category->products[category->productCount] = product;
    category->productCount++;

}void updateCategory(Category* category, const char* name) {
    if (category) {
        strncpy(category->name, name, sizeof(category->name) - 1);
        category->name[sizeof(category->name) - 1] = '\0'; 
    }
}

void printCategory(Category* category) {
    if (category) {
        printf("Category: %s\n", category->name);
        printf("  Products:\n");
        for (int i = 0; i < category->productCount; i++) {
            printf("  %d. %s \n", i + 1, category->products[i]->name);
        }
    }
}
 
void printCategoryName(Category* category) {
    if (category) {
        printf("Category: %s\n", category->name);

    }
}

void freeCategory(Category* category) {
    if (category) {
        for (int i = 0; i < category->productCount; i++) {
            free(category->products[i]->description);
            free(category->products[i]); 
        }
        free(category->products);
        free(category); 
    }
}
