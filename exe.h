#define _CRT_SECURE_NO_WARNINGS
#ifndef EXE_H
#define EXE_H
#include "address.h"
#include "brand.h"
#include "category.h"
#include "customer.h"
#include "date.h"
#include "order.h"
#include "product.h"
#include "supplier.h"
#include "user.h"
#include "ProductManager.h"
#include "BrandManager.h"
#include "categoryManager.h"
#include "CustomerManager.h"
#include "OrderManager.h"
#include "SupplierManager.h"
#include "CommonFunctions.h"

ProductManager* initProductManager();

ProductManager* starterProductManager();

BrandManager* initBrandManager();

BrandManager* starterBrandManager();

CategoryManager* initCategoryManager();

CategoryManager* starterCategoryManager();

CustomerManager* initCustomerManager();

CustomerManager* starterCustomerManager();

OrderManager* initOrderManager();

OrderManager* starterOrderManager();

SupplierManager* initSupplierManager();

SupplierManager* starterSupplierManager();

void loadFromTextFile();
void loadFromBinaryFile();
void saveSystemToFile();
void saveToBinaryFile();
void sortProductsByName();
void sortProductsByCode();
void sortProductsByPrice();
void sortProductsByCategory();
void sortProductsBySupplier();
void sortProductsByBrand();
int compareProductsBySupplier(const void* a, const void* b);
int compareProductsByName(const void* a, const void* b);
int compareProductsByCode(const void* a, const void* b);
int compareProductsByPrice(const void* a, const void* b);
int compareProductsByCategory(const void* a, const void* b);
int compareProductsByBrand(const void* a, const void* b);
void searchProductsByName();
void searchProductsByCode();
void searchProductsByPrice();
void searchProductsBySupplier();
void searchProductsByBrand();
void searchProductsByCategory();
void addProducts();
void addCategorys();
void addSuppliers();
void addOrders();
void addCustomers();
void addBrands();
void updateProducts();
void deleteProducts();
void deleteCategorys();
void deleteSuppliers();
void deleteCustomers();
void deleteBrands();
void deleteOrders();
void displayProducts();
void displayCustomers();
void displaySuppliers();
void displayOrders();
void displayBrands();
void displayCategorys();
void displaySystem();
void connectProductsToEntities(ProductManager* productManager, BrandManager* brandManager, CategoryManager* categoryManager, SupplierManager* supplierManager);
#endif
