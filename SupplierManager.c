#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exe.h"

SupplierManager* createSupplierManager() {
    SupplierManager* spplierManager = (SupplierManager*)malloc(sizeof(SupplierManager));
    if (spplierManager) {
        spplierManager->suppliers = NULL; 
        spplierManager->size = 0;
    }
    return spplierManager;
}

void addSupplier(SupplierManager* spplierManager, Supplier* newSupplier) {
    if (!spplierManager || !newSupplier) return;

    Supplier** temp = (Supplier**)realloc(spplierManager->suppliers, (spplierManager->size + 1) * sizeof(Supplier*));
    if (temp == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    spplierManager->suppliers = temp;    
    spplierManager->suppliers[spplierManager->size] = newSupplier;
    spplierManager->size++;
}

Supplier* findSupplier(SupplierManager* spplierManager, const char* companyName) {
    if (!spplierManager) return NULL;

    for (int i = 0; i < spplierManager->size; i++) {
        if (strcmp(spplierManager->suppliers[i]->companyName, companyName) == 0) {
            return spplierManager->suppliers[i];
        }
    }
    return NULL;
}

void deleteSupplier(SupplierManager* supplierManager, const char* companyName) {
    if (!supplierManager || !companyName) return;

    for (int i = 0; i < supplierManager->size; i++) {
        if (strcmp(supplierManager->suppliers[i]->companyName, companyName) == 0) {
            if (supplierManager->suppliers[i]) {
                freeSupplier(supplierManager->suppliers[i]);
            }
            for (int j = i; j < supplierManager->size - 1; j++) {
                supplierManager->suppliers[j] = supplierManager->suppliers[j + 1];
            }
            Supplier** temp = (Supplier**)realloc(supplierManager->suppliers, (supplierManager->size - 1) * sizeof(Supplier*));
            if (temp || supplierManager->size - 1 == 0) { 
                supplierManager->suppliers = temp;
                supplierManager->size--;
            }
            else {
                fprintf(stderr, "Error: Memory reallocation failed while deleting supplier.\n");
            }
            return;
        }
    }

    printf("Supplier with the company name '%s' not found.\n", companyName);
}
void printSupplierManager(SupplierManager* list) {
    if (!list) return;

    for (int i = 0; i < list->size; i++) {
        printf("\n%d. ", i + 1);
        printSupplier(list->suppliers[i]);
    }
}
void printShortSupplierManager(SupplierManager* list) {
    if (!list) return;
    for (int i = 0; i < list->size; i++) {
        printf("\n%d. ", i + 1);
        printSupplierName(list->suppliers[i]);
    }
}


void freeSupplierManager(SupplierManager* list) {
    if (!list) return;

    for (int i = 0; i < list->size; i++) {
        freeSupplier(list->suppliers[i]);
    }
    free(list->suppliers);
    free(list);
}
Supplier* findSupplierByName(SupplierManager* supplierManager, const char* supplierName) {
    if (!supplierManager || !supplierName) {
        return NULL;
    }

    for (int i = 0; i < supplierManager->size; i++) {
        if (strcmp(supplierManager->suppliers[i]->companyName, supplierName) == 0) {
            return supplierManager->suppliers[i];
        }
    }
    return NULL;
}