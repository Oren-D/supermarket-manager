#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "exe.h"

int main() {
    int choice, componentChoice, sortChoice;
    int exitProgram = 0;
    while (!exitProgram) {
        printf("\n===== Main Menu =====\n");
        printf("1. Upload system from text or binary file\n");
        printf("2. Display system\n");
        printf("3. Display subcomponents\n");
        printf("4. Add components to the system\n");
        printf("5. Sort products in system\n");
        printf("6. Search products in system\n");
        printf("7. Update products in system\n");
        printf("8. Remove components\n");
        printf("9. Save system to text or binary file\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("1. Upload system from text file\n");
            printf("2. Upload system from binary file\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &componentChoice);
            switch (componentChoice) {
            case 1: loadFromTextFile(); break;
            case 2: loadFromBinaryFile(); break;
            case 0: break;
            default: printf("Invalid choice. Please try again.\n");
            }
            break;
        case 2:
            displaySystem();
                break;
        case 3:
            printf("\n===== Display Subcomponents =====\n");
            printf("1. Display Products\n");
            printf("2. Display Customers\n");
            printf("3. Display Suppliers\n");
            printf("4. Display Orders\n");
            printf("5. Display Brands\n");
            printf("6. Display Categorys\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &componentChoice);

            switch (componentChoice) {
            case 1: displayProducts(); break;
            case 2: displayCustomers(); break;
            case 3: displaySuppliers(); break;
            case 4: displayOrders(); break;
            case 5: displayBrands(); break;
            case 6: displayCategorys(); break;
            case 0: break;
            default: printf("Invalid choice. Please try again.\n");
            }
            break;
        case 4:
            printf("\n===== Add Menu =====\n");
            printf("1. Add Product\n");
            printf("2. Add Customer\n");
            printf("3. Add Supplier\n");
            printf("4. Add Brand\n");
            printf("5. Add Category\n");
            printf("6. Add Order\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &componentChoice);

            switch (componentChoice) {
            case 1: addProducts(); break;
            case 2: addCustomers(); break;
            case 3: addSuppliers(); break;
            case 4: addBrands(); break;
            case 5: addCategorys(); break;
            case 6: addOrders(); break;
            case 0: break;
            default: printf("Invalid choice. Please try again.\n");
                break;
            }
            break;
        case 5:
            printf("\n===== Sort Menu =====\n");
            printf("1. Sort Products by name\n");
            printf("2. Sort Products by code\n");
            printf("3. Sort Products by price\n");
            printf("4. Sort Products by category\n");
            printf("5. Sort Products by supplier\n");
            printf("6. Sort Products by brand\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &componentChoice);

            switch (componentChoice) {
            case 1:
                sortProductsByName();
                break;
            case 2:
                sortProductsByCode();
                break;
            case 3:
                sortProductsByPrice();
                break;
            case 4:
                sortProductsByCategory();
                break;
            case 5:
                sortProductsBySupplier();
                break;
            case 6:
                sortProductsByBrand();
                break;
            default: printf("Invalid component choice.\n");
            }
            break;
        case 6:
            printf("\n===== Find Menu =====\n");
            printf("1. Find Product by name\n");
            printf("2. Find Product by code\n");
            printf("3. Find Product by price\n");
            printf("4. Find Product by supplier\n");
            printf("5. Find Product by brand\n");
            printf("6. Find Product by category\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &componentChoice);

            switch (componentChoice) {
            case 1: searchProductsByName(); break;
            case 2: searchProductsByCode(); break;
            case 3: searchProductsByPrice(); break;
            case 4: searchProductsBySupplier(); break;
            case 5: searchProductsByBrand(); break;
            case 6: searchProductsByCategory(); break;

            case 0: break;
            default: printf("Invalid choice. Please try again.\n");
            }
            break;
        case 7:
            updateProducts();
            break;
        case 8:
            printf("\n===== Remove Menu =====\n");
            printf("1. Remove Product\n");
            printf("2. Remove Customer\n");
            printf("3. Remove Supplier\n");
            printf("4. Remove Brand\n");
            printf("5. Remove Category\n");
            printf("6. Remove Customer\n");
            printf("7. Remove Order\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &componentChoice);

            switch (componentChoice) {
            case 1: deleteProducts(); break;
            case 2: deleteCustomers(); break;
            case 3: deleteSuppliers(); break;
            case 4: deleteBrands(); break;
            case 5: deleteCategorys(); break;
            case 6: deleteCustomers(); break;
            case 7: deleteOrders(); break;
            case 0: break;
            default: printf("Invalid choice. Please try again.\n");
            }
            break;
        case 9:
            printf("1. Save system to text file\n");
            printf("2. Save system to binary file\n");
            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &componentChoice);
            switch (componentChoice) {
            case 1: saveSystemToFile(); break;
            case 2: saveToBinaryFile(); break;
            case 0: break;
            default: printf("Invalid choice. Please try again.\n");
            }
            break;
        case 0:
            printf("Exiting program...\n");
            exitProgram = 1;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
