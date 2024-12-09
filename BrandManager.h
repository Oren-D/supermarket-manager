#ifndef BRAND_MANAGER_H
#define BRAND_MANAGER_H

#include "brand.h"

typedef struct {
    Brand** brands;
    int brandCount;
} BrandManager;

BrandManager* createBrandManager();
void addBrand(BrandManager* manager, Brand* brand);
Brand* findBrand(BrandManager* manager, const char* name);
void deleteBrandFromManager(BrandManager* manager, const char* name);
void printBrandManager(BrandManager* manager);
void freeBrandManager(BrandManager* manager);
void  printShortBrandManager(BrandManager* manager);
Brand* findBrandByName(BrandManager* brandManager, const char* brandName);

#endif // BRAND_MANAGER_H
