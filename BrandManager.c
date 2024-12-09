#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exe.h"

BrandManager* createBrandManager() {
    BrandManager* manager = (BrandManager*)malloc(sizeof(BrandManager));
    if (manager) {
        manager->brands = NULL; 
        manager->brandCount = 0;
    }
    return manager;
}

void addBrand(BrandManager* manager, Brand* brand) {
    if (!manager || !brand) return;

    manager->brands = (Brand**)realloc(manager->brands, (manager->brandCount + 1) * sizeof(Brand*));
    manager->brands[manager->brandCount] = brand;
    manager->brandCount++;
}

Brand* findBrand(BrandManager* manager, const char* name) {
    if (!manager) return NULL;

    for (int i = 0; i < manager->brandCount; i++) {
        if (strcmp(manager->brands[i]->name, name) == 0) {
            return manager->brands[i];
        }
    }
    return NULL;
}

void deleteBrandFromManager(BrandManager* manager, const char* name) {
    if (!manager || !name) return;

    for (int i = 0; i < manager->brandCount; i++) {
        if (strcmp(manager->brands[i]->name, name) == 0) {
            freeBrand(manager->brands[i]);

            for (int j = i; j < manager->brandCount - 1; j++) {
                manager->brands[j] = manager->brands[j + 1];
            }
            Brand** temp = (Brand**)realloc(manager->brands, (manager->brandCount - 1) * sizeof(Brand*));
            if (temp || manager->brandCount - 1 == 0) { 
                manager->brands = temp;
                manager->brandCount--;
            }
            else {
                fprintf(stderr, "Error: Memory reallocation failed while deleting brand.\n");
            }

            return;
        }
    }
    printf("Brand with the name '%s' not found.\n", name);
}
void printBrandManager(BrandManager* manager) {
    if (!manager) return;

    for (int i = 0; i < manager->brandCount; i++) {
        printf("\n%d. ", i + 1);
        printBrand(manager->brands[i]);
    }
}
void printShortBrandManager(BrandManager* manager) {
    for (int i = 0; i < manager->brandCount; i++) {
        printf("\n%d. ",i+1);
        printBrandName(manager->brands[i]);
    }
}

void freeBrandManager(BrandManager* manager) {
    if (!manager) return;

    for (int i = 0; i < manager->brandCount; i++) {
        freeBrand(manager->brands[i]);
    }
    free(manager->brands); 
    free(manager); 
}
Brand* findBrandByName(BrandManager* brandManager, const char* brandName) {
    if (!brandManager || !brandName) {
        return NULL;
    }
    for (int i = 0; i < brandManager->brandCount; i++) {
        if (strcasecmp(brandManager->brands[i]->name, brandName) == 0) {
            return brandManager->brands[i];
        }
    }
    return NULL;
}