#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exe.h"

CategoryManager* createCategoryManager() {
    CategoryManager* manager = (CategoryManager*)malloc(sizeof(CategoryManager));
    if (manager) {
        manager->categories = NULL; // Start with an empty manager
        manager->categoryCount = 0;
    }
    return manager;
}

void addCategory(CategoryManager* manager, Category* category) {
    if (!manager || !category) return;

    manager->categories = (Category**)realloc(manager->categories, (manager->categoryCount + 1) * sizeof(Category*));
    manager->categories[manager->categoryCount] = category;
    manager->categoryCount++;
}

Category* findCategory(CategoryManager* manager, const char* name) {
    if (!manager) return NULL;

    for (int i = 0; i < manager->categoryCount; i++) {
        if (strcmp(manager->categories[i]->name, name) == 0) {
            return manager->categories[i];
        }
    }
    return NULL;
}

void deleteCategoryFromManager(CategoryManager* manager, const char* name) {
    if (!manager) return;

    for (int i = 0; i < manager->categoryCount; i++) {
        if (strcmp(manager->categories[i]->name, name) == 0) {
            freeCategory(manager->categories[i]); // Free the category object

            // Shift the remaining elements to fill the gap
            for (int j = i; j < manager->categoryCount - 1; j++) {
                manager->categories[j] = manager->categories[j + 1];
            }

            manager->categories = (Category**)realloc(manager->categories, (manager->categoryCount - 1) * sizeof(Category*));
            manager->categoryCount--;
            return;
        }
    }
}

void printCategoryManager(CategoryManager* manager) {
    if (!manager) return;
    for (int i = 0; i < manager->categoryCount; i++) {
        printf("\n%d. ", i + 1);
        printCategory(manager->categories[i]);
    }
}
void printShortCategoryManager(CategoryManager* manager) {
    if (!manager) return;

    for (int i = 0; i < manager->categoryCount; i++) {
        printf("\n%d. ", i + 1);
        printCategoryName(manager->categories[i]);
    }
}


void freeCategoryManager(CategoryManager* manager) {
    if (!manager) return;

    for (int i = 0; i < manager->categoryCount; i++) {
        freeCategory(manager->categories[i]);
    }
    free(manager->categories); // Free the array of category pointers
    free(manager); // Free the CategoryManager object itself
}
Category* findCategoryByName(CategoryManager* categoryManager, const char* categoryName) {
    if (!categoryManager || !categoryName) {
        return NULL;
    }

    for (int i = 0; i < categoryManager->categoryCount; i++) {
        if (strcasecmp(categoryManager->categories[i]->name, categoryName) == 0) {
            return categoryManager->categories[i];
        }
    }
    return NULL;
}