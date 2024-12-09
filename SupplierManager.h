#ifndef SUPPLIER_MANAGER_H
#define SUPPLIER_MANAGER_H

#include "supplier.h"

typedef struct {
    Supplier** suppliers;
    int size;
} SupplierManager;

SupplierManager* createSupplierManager();
void addSupplier(SupplierManager* supplierManager, Supplier* newSupplier);
Supplier* findSupplier(SupplierManager* supplierManager, const char* companyName);
void deleteSupplier(SupplierManager* supplierManager, const char* companyName);
void printSupplierManager(SupplierManager* supplierManager);
void printShortSupplierManager(SupplierManager* list);
void freeSupplierManager(SupplierManager* supplierManager);
Supplier* findSupplierByName(SupplierManager* supplierManager, const char* supplierName);

#endif // SUPPLIER_MANAGER_H
