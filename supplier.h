#ifndef SUPPLIER_H
#define SUPPLIER_H

#include "address.h"
#include "product.h"

typedef struct {
    char* companyName;
    char phone[20];
    Address address;
    Product** suppliedProducts;
    int numOfProducts;
} Supplier;

Supplier* createSupplier(const char* companyName, const char* phone, Address address);
void addProductToSupplier(Supplier* supplier, Product* product);
void updateSupplier(Supplier* supplier, const char* companyName, const char* phone, Address address);
void printSupplier(Supplier* supplier);
void printSupplierName(Supplier* supplier);
void freeSupplier(Supplier* supplier);

#endif // SUPPLIER_H
