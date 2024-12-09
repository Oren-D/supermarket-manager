#ifndef CATEGORY_MANAGER_H
#define CATEGORY_MANAGER_H

#include "category.h"

typedef struct {
    Category** categories;
    int categoryCount;
} CategoryManager;

CategoryManager* createCategoryManager();
void addCategory(CategoryManager* manager, Category* category);
Category* findCategory(CategoryManager* manager, const char* name);
void deleteCategoryFromManager(CategoryManager* manager, const char* name);
void printCategoryManager(CategoryManager* manager);
void printShortCategoryManager(CategoryManager* manager);
void freeCategoryManager(CategoryManager* manager);
Category* findCategoryByName(CategoryManager* categoryManager, const char* categoryName);

#endif // CATEGORY_MANAGER_H
