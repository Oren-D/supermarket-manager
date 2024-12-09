#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "supplier.h"

Supplier* createSupplier(const char* companyName, const char* phone, Address address) {
    Supplier* supplier = (Supplier*)malloc(sizeof(Supplier));
    if (supplier) {
        supplier->companyName = (char*)malloc((strlen(companyName) + 1) * sizeof(char));
        if (!supplier->companyName) {
            fprintf(stderr, "Error: Memory allocation failed for company name\n");
            free(supplier); 
            return NULL;
        }
        strcpy(supplier->companyName, companyName); 

        strcpy(supplier->phone, phone);

        supplier->address = address; 
        supplier->suppliedProducts = NULL; 
        supplier->numOfProducts = 0;
    }
    return supplier;
}

void updateSupplier(Supplier* supplier, const char* companyName, const char* phone, Address address) {
    if (supplier) {
        free(supplier->companyName);

        supplier->companyName = (char*)malloc(strlen(companyName) + 1);
        if (!supplier->companyName) {
            fprintf(stderr, "Error: Memory allocation failed for supplier companyName\n");
            return; 
        }
        strcpy(supplier->companyName, companyName);
        free(supplier->phone);
        strcpy(supplier->phone, phone);

        supplier->address = address;
    }
}void addProductToSupplier(Supplier* supplier, Product* product) {
    if (!supplier || !product) {
        fprintf(stderr, "Error: Supplier or Product is NULL.\n");
        return;
    }

    Product** temp = (Product**)realloc(supplier->suppliedProducts, (supplier->numOfProducts + 1) * sizeof(Product*));
    if (!temp) {
        fprintf(stderr, "Error: Memory allocation failed for supplied products.\n");
        return;
    }

    supplier->suppliedProducts = temp;
    supplier->suppliedProducts[supplier->numOfProducts] = product;
    supplier->numOfProducts++;
}

void printSupplier(Supplier* supplier) {
    if (supplier) {
        printf("Company Name: %s\n", supplier->companyName);
        printf("Phone: %s\n", supplier->phone);
        printf("Address:\n");
        printAddress(&supplier->address);

        printf("  Products:\n");
        for (int i = 0; i < supplier->numOfProducts; i++) {
            printf("  %d. %s \n ",i+1, supplier->suppliedProducts[i]->name);
        }
    }
}
void printSupplierName(Supplier* supplier) {
    if (supplier) {
        printf("Company Name: %s\n", supplier->companyName);
    }
}

void freeSupplier(Supplier* supplier) {
    if (supplier) {
        if (supplier->companyName) {
            free(supplier->companyName);
        }
        if (supplier->suppliedProducts) {
            for (int i = 0; i < supplier->numOfProducts; i++) {
                if (supplier->suppliedProducts[i]) {
                    if (supplier->suppliedProducts[i]->description) {
                        free(supplier->suppliedProducts[i]->description);
                    }
                    free(supplier->suppliedProducts[i]);
                }
            }
            free(supplier->suppliedProducts);
        }

        
        free(supplier);
    }
}