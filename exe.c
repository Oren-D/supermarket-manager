#define _CRT_SECURE_NO_WARNINGS
#define PRINT_INFO(format, ...) printf("[Marcos] " format "\n", ##__VA_ARGS__)
#include "exe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <search.h>

ProductManager* initProductManager() {
    ProductManager* productManager = (ProductManager*)malloc(sizeof(ProductManager));
    if (productManager == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    productManager->productCount = 0;
    productManager->products = NULL;
    return productManager;
}

ProductManager* starterProductManager() {
    static ProductManager* productManager = NULL;
    if (productManager == NULL) {
        productManager = initProductManager();
    }
    return productManager;
}

BrandManager* initBrandManager() {
    BrandManager* brandManager = (BrandManager*)malloc(sizeof(BrandManager));
    if (brandManager == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    brandManager->brandCount = 0;
    brandManager->brands = NULL;
    return brandManager;
}

BrandManager* starterBrandManager() {
    static BrandManager* brandManager = NULL;
    if (brandManager == NULL) {
        brandManager = initBrandManager();
    }
    return brandManager;
}

CategoryManager* initCategoryManager() {
    CategoryManager* categoryManager = (CategoryManager*)malloc(sizeof(CategoryManager));
    if (categoryManager == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    categoryManager->categoryCount = 0;
    categoryManager->categories = NULL;
    return categoryManager;
}

CategoryManager* starterCategoryManager() {
    static CategoryManager* categoryManager = NULL;
    if (categoryManager == NULL) {
        categoryManager = initCategoryManager();
    }
    return categoryManager;
}

CustomerManager* initCustomerManager() {
    CustomerManager* customerManager = (CustomerManager*)malloc(sizeof(CustomerManager));
    if (customerManager == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    customerManager->head = NULL;
    customerManager->tail = NULL;
    return customerManager;
}

CustomerManager* starterCustomerManager() {
    static CustomerManager* customerManager = NULL;
    if (customerManager == NULL) {
        customerManager = initCustomerManager();
    }
    return customerManager;
}

OrderManager* initOrderManager() {
    OrderManager* orderManager = (OrderManager*)malloc(sizeof(OrderManager));
    if (orderManager == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    orderManager->head = NULL;
    orderManager->size = 0;
    return orderManager;
}

OrderManager* starterOrderManager() {
    static OrderManager* orderManager = NULL;
    if (orderManager == NULL) {
        orderManager = initOrderManager();
    }

    return orderManager;
}

SupplierManager* initSupplierManager() {
    SupplierManager* supplierManager = (SupplierManager*)malloc(sizeof(SupplierManager));
    if (supplierManager == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    supplierManager->size = 0;
    supplierManager->suppliers = NULL;
    return supplierManager;
}

SupplierManager* starterSupplierManager() {
    static SupplierManager* supplierManager = NULL;
    if (supplierManager == NULL) {
        supplierManager = initSupplierManager();
    }
    return supplierManager;
}

void loadFromTextFile() {
    FILE* file = fopen("data.txt", "r");
    if (!file) {
        printf("Failed to open file: data.txt\n");
        return;
    }

    ProductManager* productManager = starterProductManager();
    CategoryManager* categoryManager = starterCategoryManager();
    BrandManager* brandManager = starterBrandManager();
    SupplierManager* supplierManager = starterSupplierManager();
    CustomerManager* customerManager = starterCustomerManager();
    OrderManager* orderManager = starterOrderManager();

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char* trimmedLine = strtok(line, "\n");

        if (trimmedLine[0] == '#') {
            if (strcmp(trimmedLine, "# BrandManager") == 0) {
                int brandCount;
                if(fscanf(file, "BrandCount: %d\n", &brandCount)!=1){}
                for (int i = 0; i < brandCount; i++) {
                    char name[50];
                    if (fscanf(file, "Brand:\n") != 1) {
                    }
                    if (fscanf(file, "    Name: %49[^\n]\n", name) != 1) {
                    }

                    Brand* newBrand = createBrand(name);
                    if (newBrand) {
                        addBrand(brandManager, newBrand);
                    }
                }
            }
            else if (strcmp(trimmedLine, "# CategoryManager") == 0) {
                int categoryCount;
                if(fscanf(file, "CategoryCount: %d\n", &categoryCount)!=1){}
                for (int i = 0; i < categoryCount; i++) {
                    char name[50];
                  if(fscanf(file, "Category:\n")!=1){}
                   if( fscanf(file, "    Name: %49[^\n]\n", name)!=1){}

                    Category* newCategory = createCategory(name);
                    if (newCategory) {
                        addCategory(categoryManager, newCategory);
                    }
                }
            }
            else if (strcmp(trimmedLine, "# SupplierManager") == 0) {
                int supplierCount;
                if(fscanf(file, "SupplierCount: %d\n", &supplierCount)!=1){}
                for (int i = 0; i < supplierCount; i++) {
                    char companyName[50], phone[20];
                    Address address;

                   if(fscanf(file, "Supplier:\n")!=1){}
                    if(fscanf(file, "    Name: %49[^\n]\n", companyName)!=1){}
                   if(fscanf(file, "    Phone: %19[^\n]\n", phone)!=1){}
                   if(fscanf(file, "    Address:\n")!=1){}
                    if(fscanf(file, "        Street: %99[^\n]\n", address.street)!=1){}
                    if(fscanf(file, "        City: %49[^\n]\n", address.city)!=1){}
                    if(fscanf(file, "        PostalCode: %d\n", &address.postalCode)!=1){}

                    Supplier* newSupplier = createSupplier(companyName, phone, address);
                    if (newSupplier) {
                        addSupplier(supplierManager, newSupplier);
                    }
                }
            }
            else if (strcmp(trimmedLine, "# ProductManager") == 0) {
                int productCount;
                if(fscanf(file, "ProductCount: %d\n", &productCount)!=1){}
                for (int i = 0; i < productCount; i++) {
                    char name[50], description[100], brandName[50], categoryName[50], supplierName[50];
                    Date manufactureDate;
                    double price;
                    int productID;

                    if(fscanf(file, "Product:\n")!=1){}
                    if(fscanf(file, "    ID: %d\n", &productID)!=1){}
                    if(fscanf(file, "    Name: %49[^\n]\n", name)!=1){}
                    if(fscanf(file, "    Description: %99[^\n]\n", description)!=1){}
                    if(fscanf(file, "    Price: %lf\n", &price)!=1){}
                    if(fscanf(file, "    ManufactureDate: %d-%d-%d\n", &manufactureDate.year, &manufactureDate.month, &manufactureDate.day)!=1){}
                    if(fscanf(file, "    Brand: %49[^\n]\n", brandName)!=1){}
                    if(fscanf(file, "    Category: %49[^\n]\n", categoryName)!=1){}
                    if(fscanf(file, "    Supplier: %49[^\n]\n", supplierName)!=1){}

                    Product* newProduct = createProduct(name, description, productID, price, manufactureDate, brandName, categoryName, supplierName);
                    if (newProduct) {
                        addProductToManager(productManager, newProduct);
                    }
                }
            }
            else if (strcmp(trimmedLine, "# CustomerManager") == 0) {
                int customerCount;
                if(fscanf(file, "CustomerCount: %d\n", &customerCount)!=1){}
                for (int i = 0; i < customerCount; i++) {
                    int customerID;
                    char name[50], email[50];
                    Address CustAddress;

                    if(fscanf(file, "Customer:\n")!=1){}
                    if(fscanf(file, "    ID: %d\n", &customerID)!=1){}
                    if(fscanf(file, "    Name: %49[^\n]\n", name)!=1){}
                    if(fscanf(file, "    Email: %49[^\n]\n", email)!=1){}
                    if(fscanf(file, "    Address:\n")!=1){}
                    if(fscanf(file, "         Street: %99[^\n]\n", CustAddress.street)!=1){}
                    if(fscanf(file, "         City: %49[^\n]\n", CustAddress.city)!=1){}
                    if(fscanf(file, "         PostalCode: %d\n", &CustAddress.postalCode)!=1){}

                    Customer* newCustomer = createCustomer(name, email, customerID,&CustAddress);
                    if (newCustomer) {
                        addCustomer(customerManager, newCustomer);
                    }
                }
            }
            else if (strcmp(trimmedLine, "# OrderManager") == 0) {
                int orderCount;
                if(fscanf(file, "OrderCount: %d\n", &orderCount)!=1){}
                for (int i = 0; i < orderCount; i++) {
                    int orderID;
                    char customerName[50];
                    Date orderDate;
                    char productIDs[256];

                    if(fscanf(file, "Order:\n")!=1){}
                    if(fscanf(file, "    ID: %d\n", &orderID)!=1){}
                    if(fscanf(file, "    Customer: %49[^\n]\n", customerName)!=1){}
                    if(fscanf(file, "    Date: %d-%d-%d\n", &orderDate.year, &orderDate.month, &orderDate.day)!=3){}
                    if(fscanf(file, "    Products: %[^\n]\n", productIDs)!=1){}

                    Customer* customer = findCustomerByName(customerManager, customerName);
                    if (!customer) {
                        fprintf(stderr, "Error: Could not find customer with name %s\n", customerName);
                        continue;
                    }

                    Order* newOrder = createOrder(orderID, customer, orderDate);
                    if (!newOrder) {
                        fprintf(stderr, "Failed to create order with ID: %d\n", orderID);
                        continue;
                    }

                    char* token = strtok(productIDs, " ");
                    while (token) {
                        int productID = atoi(token);
                        Product* product = findProductInManager(productManager, productID);
                        if (product) {
                            addProductToOrder(newOrder, product);
                        }
                        token = strtok(NULL, " ");
                    }

                    addOrder(orderManager, newOrder);
                }
            }
        }
        else {
            printf("Unexpected section header: %s\n", trimmedLine);
        }

    }
    connectProductsToEntities( productManager,  brandManager,  categoryManager,  supplierManager);

    fclose(file);
    printf("System loaded successfully.\n");
}
void connectProductsToEntities(ProductManager* productManager, BrandManager* brandManager, CategoryManager* categoryManager, SupplierManager* supplierManager) {
    for (int i = 0; i < productManager->productCount; i++) {
        Product* product = productManager->products[i];

        Brand* brand = findBrandByName(brandManager, product->brandName);
        if (brand) {
            addProductToBrand(brand, product);
        }
        else {
            printf("Warning: Could not find brand %s for product %s.\n", product->brandName, product->name);
        }

        Category* category = findCategoryByName(categoryManager, product->categoryName);
        if (category) {
            addProductToCategory(category, product);
        }
        else {
            printf("Warning: Could not find category %s for product %s.\n", product->categoryName, product->name);
        }
        Supplier* supplier = findSupplierByName(supplierManager, product->supplierName);
        if (supplier) {
            addProductToSupplier(supplier, product);
        }
        else {
            printf("Warning: Could not find supplier %s for product %s.\n", product->supplierName, product->name);
        }
    }

}
void loadFromBinaryFile() {
    FILE* file = fopen("data.bin", "rb");
    if (!file) {
        printf("Failed to open binary file: data.bin\n");
        return;
    }

    ProductManager* productManager = starterProductManager();
    CategoryManager* categoryManager = starterCategoryManager();
    BrandManager* brandManager = starterBrandManager();
    SupplierManager* supplierManager = starterSupplierManager();
    CustomerManager* customerManager = starterCustomerManager();
    OrderManager* orderManager = starterOrderManager();

    int productCount;
    fread(&productCount, sizeof(int), 1, file);
    printf("Loading %d products\n", productCount);
    if (productCount <= 0) {
        printf("Error: Invalid product count.\n");
        fclose(file);
        return;
    }
    for (int i = 0; i < productCount; i++) {
        int nameLen, descriptionLen, brandNameLen, categoryNameLen, supplierNameLen;
        Product* product = createProduct("", "", 0, 0.0, (Date) { 0, 0, 0 }, "", "", "");

        fread(&product->productID, sizeof(int), 1, file);
        fread(&product->price, sizeof(double), 1, file);
        fread(&product->manufactureDate, sizeof(Date), 1, file);

        fread(&nameLen, sizeof(int), 1, file);
        if (nameLen <= 0) {
            printf("Error: Invalid product name length.\n");
            fclose(file);
            return;
        }
        fread(product->name, sizeof(char), nameLen, file);

        fread(&descriptionLen, sizeof(int), 1, file);
        if (descriptionLen <= 0) {
            printf("Error: Invalid product description length.\n");
            fclose(file);
            return;
        }
        product->description = (char*)malloc(descriptionLen * sizeof(char));
        fread(product->description, sizeof(char), descriptionLen, file);

        fread(&brandNameLen, sizeof(int), 1, file);
        if (brandNameLen <= 0) {
            printf("Error: Invalid brand name length.\n");
            fclose(file);
            return;
        }
        product->brandName = (char*)malloc(brandNameLen * sizeof(char));
        fread(product->brandName, sizeof(char), brandNameLen, file);

        fread(&categoryNameLen, sizeof(int), 1, file);
        if (categoryNameLen <= 0) {
            printf("Error: Invalid category name length.\n");
            fclose(file);
            return;
        }
        product->categoryName = (char*)malloc(categoryNameLen * sizeof(char));
        fread(product->categoryName, sizeof(char), categoryNameLen, file);

        fread(&supplierNameLen, sizeof(int), 1, file);
        if (supplierNameLen <= 0) {
            printf("Error: Invalid supplier name length.\n");
            fclose(file);
            return;
        }
        product->supplierName = (char*)malloc(supplierNameLen * sizeof(char));
        fread(product->supplierName, sizeof(char), supplierNameLen, file);

        printf("Loaded product: %s, ID: %d\n", product->name, product->productID);  

        addProductToManager(productManager, product);
    }

    int categoryCount;
    fread(&categoryCount, sizeof(int), 1, file);
    printf("Loading %d categories\n", categoryCount);  
    if (categoryCount <= 0) {
        printf("Error: Invalid category count.\n");
        fclose(file);
        return;
    }
    for (int i = 0; i < categoryCount; i++) {
        int nameLen;
        fread(&nameLen, sizeof(int), 1, file);
        if (nameLen <= 0) {
            printf("Error: Invalid category name length.\n");
            fclose(file);
            return;
        }
        char* name = (char*)malloc(nameLen * sizeof(char));
        fread(name, sizeof(char), nameLen, file);
        printf("Loaded category: %s\n", name);  

        Category* category = createCategory(name);
        free(name);  
        addCategory(categoryManager, category);
    }

    int brandCount;
    fread(&brandCount, sizeof(int), 1, file);
    printf("Loading %d brands\n", brandCount);  
    if (brandCount <= 0) {
        printf("Error: Invalid brand count.\n");
        fclose(file);
        return;
    }
    for (int i = 0; i < brandCount; i++) {
        int nameLen;
        fread(&nameLen, sizeof(int), 1, file);
        if (nameLen <= 0) {
            printf("Error: Invalid brand name length.\n");
            fclose(file);
            return;
        }
        char* name = (char*)malloc(nameLen * sizeof(char));
        fread(name, sizeof(char), nameLen, file);
        printf("Loaded brand: %s\n", name);  

        Brand* brand = createBrand(name);
        free(name);  
        addBrand(brandManager, brand);
    }
    int supplierCount;
    fread(&supplierCount, sizeof(int), 1, file);
    printf("Loading %d suppliers\n", supplierCount);  
    if (supplierCount <= 0) {
        printf("Error: Invalid supplier count.\n");
        fclose(file);
        return;
    }
    for (int i = 0; i < supplierCount; i++) {
        int nameLen, phoneLen;
        fread(&nameLen, sizeof(int), 1, file);
        if (nameLen <= 0) {
            printf("Error: Invalid supplier name length.\n");
            fclose(file);
            return;
        }
        char* companyName = (char*)malloc(nameLen * sizeof(char));
        fread(companyName, sizeof(char), nameLen, file);

        fread(&phoneLen, sizeof(int), 1, file);
        if (phoneLen <= 0) {
            printf("Error: Invalid supplier phone length.\n");
            free(companyName);
            fclose(file);
            return;
        }
        char* phone = (char*)malloc(phoneLen * sizeof(char));
        fread(phone, sizeof(char), phoneLen, file);

        Address address;
        fread(&address, sizeof(Address), 1, file);
        printf("Loaded supplier: %s, Phone: %s\n", companyName, phone); 

        Supplier* supplier = createSupplier(companyName, phone, address);
        free(companyName);  
        free(phone);  
        addSupplier(supplierManager, supplier);
    }

    int customerCount;
    fread(&customerCount, sizeof(int), 1, file);
    printf("Loading %d customers\n", customerCount); 
    if (customerCount <= 0) {
        printf("Error: Invalid customer count.\n");
        fclose(file);
        return;
    }
    for (int i = 0; i < customerCount; i++) {
        int nameLen, emailLen;
        Customer* customer = createCustomer("", "", 0, (Address*)malloc(sizeof(Address)));

        fread(&customer->customerID, sizeof(int), 1, file);

        fread(&nameLen, sizeof(int), 1, file);
        if (nameLen <= 0) {
            printf("Error: Invalid customer name length.\n");
            fclose(file);
            return;
        }
        customer->name = (char*)malloc(nameLen * sizeof(char));
        fread(customer->name, sizeof(char), nameLen, file);

        fread(&emailLen, sizeof(int), 1, file);
        if (emailLen <= 0) {
            printf("Error: Invalid customer email length.\n");
            fclose(file);
            return;
        }
        fread(customer->email, sizeof(char), emailLen, file);

        fread(customer->address, sizeof(Address), 1, file);
        printf("Loaded customer: %s, ID: %d\n", customer->name, customer->customerID);  

        addCustomer(customerManager, customer);
    }

    int orderCount;
    fread(&orderCount, sizeof(int), 1, file);
    printf("Loading %d orders\n", orderCount);  
    if (orderCount <= 0) {
        printf("Error: Invalid order count.\n");
        fclose(file);
        return;
    }
    for (int i = 0; i < orderCount; i++) {
        int orderID, productCount;
        Date orderDate;
        int customerNameLen;
        fread(&orderID, sizeof(int), 1, file);

        fread(&customerNameLen, sizeof(int), 1, file);
        if (customerNameLen <= 0) {
            printf("Error: Invalid order customer name length.\n");
            fclose(file);
            return;
        }
        char* customerName = (char*)malloc(customerNameLen * sizeof(char));
        if (customerName == NULL) {
            printf("Error: Memory allocation failed for customerName.\n");
            fclose(file);
            return;
        }
        fread(customerName, sizeof(char), customerNameLen, file);
        fread(&orderDate, sizeof(Date), 1, file);

        Customer* customer = findCustomerByName(customerManager, customerName);
        free(customerName);
        if (!customer) {
            fprintf(stderr, "Error: Could not find customer.\n");
            continue;
        }

        Order* order = createOrder(orderID, customer, orderDate);
        fread(&productCount, sizeof(int), 1, file);
        for (int j = 0; j < productCount; j++) {
            int productID;
            fread(&productID, sizeof(int), 1, file);
            Product* product = findProductInManager(productManager, productID);
            if (product) {
                addProductToOrder(order, product);
            }
        }
        printf("Loaded order: ID: %d, Customer: %s\n", orderID, customer->name);  
        addOrder(orderManager, order);
    }

    connectProductsToEntities(productManager, brandManager, categoryManager, supplierManager);

    fclose(file);
    printf("System loaded successfully from binary file.\n");
}
void saveToBinaryFile() {
    FILE* file = fopen("data.bin", "wb");
    if (!file) {
        printf("Error: Could not open binary file for writing.\n");
        return;
    }
    ProductManager* productManager = starterProductManager();
    fwrite(&productManager->productCount, sizeof(int), 1, file);
    for (int i = 0; i < productManager->productCount; i++) {
        Product* product = productManager->products[i];
        fwrite(&product->productID, sizeof(int), 1, file);
        fwrite(&product->price, sizeof(double), 1, file);
        fwrite(&product->manufactureDate, sizeof(Date), 1, file);
        size_t length = strlen(product->name) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(product->name, sizeof(char), length, file);

        length = strlen(product->description) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(product->description, sizeof(char), length, file);

        length = strlen(product->brandName) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(product->brandName, sizeof(char), length, file);

        length = strlen(product->categoryName) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(product->categoryName, sizeof(char), length, file);

        length = strlen(product->supplierName) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(product->supplierName, sizeof(char), length, file);
    }

    CategoryManager* categoryManager = starterCategoryManager();
    fwrite(&categoryManager->categoryCount, sizeof(int), 1, file);
    for (int i = 0; i < categoryManager->categoryCount; i++) {
        Category* category = categoryManager->categories[i];
        size_t length = strlen(category->name) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(category->name, sizeof(char), length, file);
    }
    BrandManager* brandManager = starterBrandManager();
    fwrite(&brandManager->brandCount, sizeof(int), 1, file);
    for (int i = 0; i < brandManager->brandCount; i++) {
        Brand* brand = brandManager->brands[i];
        size_t length = strlen(brand->name) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(brand->name, sizeof(char), length, file);
    }

    SupplierManager* supplierManager = starterSupplierManager();
    fwrite(&supplierManager->size, sizeof(int), 1, file);
    for (int i = 0; i < supplierManager->size; i++) {
        Supplier* supplier = supplierManager->suppliers[i];

        size_t length = strlen(supplier->companyName) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(supplier->companyName, sizeof(char), length, file);

        length = strlen(supplier->phone) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(supplier->phone, sizeof(char), length, file);

        fwrite(&supplier->address, sizeof(Address), 1, file);
    }
    CustomerManager* customerManager = starterCustomerManager();
    DListNode* currentCustomer = customerManager->head;
    int customerCount = 0;
    while (currentCustomer) {
        customerCount++;
        currentCustomer = currentCustomer->next;
    }
    fwrite(&customerCount, sizeof(int), 1, file);
    currentCustomer = customerManager->head;
    while (currentCustomer) {
        Customer* customer = currentCustomer->data;

        fwrite(&customer->customerID, sizeof(int), 1, file);

        size_t length = strlen(customer->name) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(customer->name, sizeof(char), length, file);

        length = strlen(customer->email) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(customer->email, sizeof(char), length, file);

        fwrite(customer->address, sizeof(Address), 1, file);

        currentCustomer = currentCustomer->next;
    }
    OrderManager* orderManager = starterOrderManager();
    fwrite(&orderManager->size, sizeof(int), 1, file);
    OrderNode* currentOrder = orderManager->head;
    while (currentOrder) {
        Order* order = currentOrder->data;
        fwrite(&order->orderID, sizeof(int), 1, file);

        size_t length = strlen(order->customer->name) + 1;
        fwrite(&length, sizeof(int), 1, file);
        fwrite(order->customer->name, sizeof(char), length, file);

        fwrite(&order->orderDate, sizeof(Date), 1, file);

        fwrite(&order->numOfProducts, sizeof(int), 1, file);
        for (int i = 0; i < order->numOfProducts; i++) {
            fwrite(&order->orderedProducts[i]->productID, sizeof(int), 1, file);
        }

        currentOrder = currentOrder->next;
    }
    fclose(file);
    printf("System saved successfully to data.bin\n");
}
void saveSystemToFile() {
    FILE* file = fopen("data.txt", "w");
    if (!file) {
        printf("Error: Could not open file for writing.\n");
        return;
    }
    ProductManager* productManager = starterProductManager();
    fprintf(file, "# ProductManager\n");
    fprintf(file, "ProductCount: %d\n", productManager->productCount);
    for (int i = 0; i < productManager->productCount; i++) {
        Product* product = productManager->products[i];
        fprintf(file, "Product:\n");
        fprintf(file, "    ID: %d\n", product->productID);
        fprintf(file, "    Name: %s\n", product->name);
        fprintf(file, "    Description: %s\n", product->description);
        fprintf(file, "    Price: %.2f\n", product->price);
        fprintf(file, "    ManufactureDate: %04d-%02d-%02d\n", product->manufactureDate.year, product->manufactureDate.month, product->manufactureDate.day);
        fprintf(file, "    Brand: %s\n", product->brandName);
        fprintf(file, "    Category: %s\n", product->categoryName);
        fprintf(file, "    Supplier: %s\n", product->supplierName);
    }
    CategoryManager* categoryManager = starterCategoryManager();
    fprintf(file, "\n# CategoryManager\n");
    fprintf(file, "CategoryCount: %d\n", categoryManager->categoryCount);
    for (int i = 0; i < categoryManager->categoryCount; i++) {
        Category* category = categoryManager->categories[i];
        fprintf(file, "Category:\n");
        fprintf(file, "    Name: %s\n", category->name);
    }
    BrandManager* brandManager = starterBrandManager();
    fprintf(file, "\n# BrandManager\n");
    fprintf(file, "BrandCount: %d\n", brandManager->brandCount);
    for (int i = 0; i < brandManager->brandCount; i++) {
        Brand* brand = brandManager->brands[i];
        fprintf(file, "Brand:\n");
        fprintf(file, "    Name: %s\n", brand->name);
    }
    SupplierManager* supplierManager = starterSupplierManager();
    fprintf(file, "\n# SupplierManager\n");
    fprintf(file, "SupplierCount: %d\n", supplierManager->size);
    for (int i = 0; i < supplierManager->size; i++) {
        Supplier* supplier = supplierManager->suppliers[i];
        fprintf(file, "Supplier:\n");
        fprintf(file, "    Name: %s\n", supplier->companyName);
        fprintf(file, "    Phone: %s\n", supplier->phone);
        fprintf(file, "    Address:\n");
        fprintf(file, "        Street: %s\n", supplier->address.street);
        fprintf(file, "        City: %s\n", supplier->address.city);
        fprintf(file, "        PostalCode: %d\n", supplier->address.postalCode);
    }
    CustomerManager* customerManager = starterCustomerManager();
    fprintf(file, "\n# CustomerManager\n");
    DListNode* currentCustomer = customerManager->head;
    int customerCount = 0;
    while (currentCustomer) {
        customerCount++;
        currentCustomer = currentCustomer->next;
    }
    fprintf(file, "CustomerCount: %d\n", customerCount);
    currentCustomer = customerManager->head;
    while (currentCustomer) {
        Customer* customer = currentCustomer->data;
        fprintf(file, "Customer:\n");
        fprintf(file, "    ID: %d\n", customer->customerID);
        fprintf(file, "    Name: %s\n", customer->name);
        fprintf(file, "    Email: %s\n", customer->email);
        fprintf(file, "    Address:\n");
        fprintf(file, "        Street: %s\n", customer->address->street);
        fprintf(file, "        City: %s\n", customer->address->city);
        fprintf(file, "        PostalCode: %d\n", customer->address->postalCode);
        currentCustomer = currentCustomer->next;
    }
    OrderManager* orderManager = starterOrderManager();
    fprintf(file, "\n# OrderManager\n");
    fprintf(file, "OrderCount: %d\n", orderManager->size);
    OrderNode* currentOrder = orderManager->head;
    while (currentOrder) {
        Order* order = currentOrder->data;
        fprintf(file, "Order:\n");
        fprintf(file, "    ID: %d\n", order->orderID);
        fprintf(file, "    Customer: %s\n", order->customer->name);
        fprintf(file, "    Date: %04d-%02d-%02d\n", order->orderDate.year, order->orderDate.month, order->orderDate.day);
        fprintf(file, "    Products:");
        for (int i = 0; i < order->numOfProducts; i++) {
            fprintf(file, " %d", order->orderedProducts[i]->productID);
        }
        fprintf(file, "\n");
        currentOrder = currentOrder->next;
    }

    fclose(file);
    printf("System saved successfully to data.txt\n");
}
int compareProductsByName(const void* a, const void* b) {

    if (a == NULL || b == NULL) {
        return 0; 
    }

    Product* prod1 = *(Product**)a;
    Product* prod2 = *(Product**)b;

    if (prod1 == NULL || prod2 == NULL) {
        return 0;
    }

    return strcmp(prod1->name, prod2->name);
}
void sortProductsByName() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products to sort.\n");
        return;
    }

    qsort(productManager->products, productManager->productCount, sizeof(Product*), compareProductsByName);
    printf("Products sorted by name.\n");
}
int compareProductsByCode(const void* a, const void* b) {
    Product* prod1 = *(Product**)a;
    Product* prod2 = *(Product**)b;
    return (prod1->productID - prod2->productID);
}
void sortProductsByCode() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products to sort.\n");
        return;
    }

    qsort(productManager->products, productManager->productCount, sizeof(Product*), compareProductsByCode);
    printf("Products sorted by code.\n");
}
int compareProductsByPrice(const void* a, const void* b) {
    Product* prod1 = *(Product**)a;
    Product* prod2 = *(Product**)b;
    if (prod1->price > prod2->price) return 1;
    if (prod1->price < prod2->price) return -1;
    return 0;
}
void sortProductsByPrice() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products to sort.\n");
        return;
    }

    qsort(productManager->products, productManager->productCount, sizeof(Product*), compareProductsByPrice);
    printf("Products sorted by price.\n");
}
void sortProductsByCategory() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products available to sort.\n");
        return;
    }

    qsort(productManager->products, productManager->productCount, sizeof(Product*), compareProductsByCategory);

    printf("Products have been sorted by category.\n");
}
void sortProductsBySupplier() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products available to sort.\n");
        return;
    }

    qsort(productManager->products, productManager->productCount, sizeof(Product*), compareProductsBySupplier);

    printf("Products have been sorted by supplier.\n");
}
void sortProductsByBrand()
{
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products available to sort.\n");
        return;
    }

    qsort(productManager->products, productManager->productCount, sizeof(Product*), compareProductsByBrand);

    printf("Products have been sorted by brand.\n");
}
int compareProductsByBrand(const void* a, const void* b) {
    Product* productA = *(Product**)a;
    Product* productB = *(Product**)b;
    return strcmp(productA->brandName, productB->brandName);
}
int compareProductsBySupplier(const void* a, const void* b) {
    Product* productA = *(Product**)a;
    Product* productB = *(Product**)b;
    return strcmp(productA->supplierName, productB->supplierName);
}
int compareProductsByCategory(const void* a, const void* b) {
    Product* productA = *(Product**)a;
    Product* productB = *(Product**)b;
    return strcmp(productA->categoryName, productB->categoryName);
}
void searchProductsByName() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products available.\n");
        return;
    }
    if (productManager->productCount > 1) {
        sortProductsByName();
    }

    char name[50];
    name[sizeof(name) - 1] = '\0';
    printf("Enter the product name to search: ");
    if (scanf(" %49[^\n]", name) != 1) {}
        Product key;
    strcpy(key.name, name);
    Product* keyPtr = &key; 
    Product** foundProduct = (Product**)bsearch(
        &keyPtr,
        productManager->products,
        productManager->productCount,
        sizeof(Product*),
        compareProductsByName
    );

    if (foundProduct && *foundProduct) {
        printProduct(*foundProduct);
    }
    else {
        printf("No product found with the name '%s'.\n", name);
    }
}
void searchProductsByCode() {
    ProductManager* productManager = starterProductManager();

    if (!productManager || productManager->productCount == 0) {
        printf("No products available.\n");
        return;
    }

    int productID;
    printf("Enter the product code to search: ");
    if (scanf("%d", &productID) != 1) {
        printf("Invalid input format.\n");
        clearInputBuffer();
        return;
    }
    sortProductsByCode();
    Product key = { 0 };  
    key.productID = productID;  

    Product* keyPtr = &key;  

    Product** foundProduct = (Product**)bsearch(
        &keyPtr,
        productManager->products,
        productManager->productCount,
        sizeof(Product*),
        compareProductsByCode
    );

    if (foundProduct && *foundProduct) {
        printf("Product found:\n");
        printProduct(*foundProduct);
    }
    else {
        printf("No product found with the code '%d'.\n", productID);
    }
}
void searchProductsByPrice() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products available to search.\n");
        return;
    }

    double targetPrice;
    printf("Enter the price to search for: ");
    if (scanf("%lf", &targetPrice) != 1) {
        printf("Invalid input format.\n");
        clearInputBuffer();
        return;
    }

    sortProductsByPrice();

    Product key = { 0 };  
    key.price = targetPrice;  

    Product* keyPtr = &key; 

    Product** foundProduct = (Product**)bsearch(
        &keyPtr,
        productManager->products,
        productManager->productCount,
        sizeof(Product*),
        compareProductsByPrice
    );

    if (foundProduct && *foundProduct) {
        printf("Product found:\n");
        printProduct(*foundProduct);
    }
    else {
        printf("No product found with the price: %.2lf\n", targetPrice);
    }
}
void searchProductsBySupplier() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products available to search.\n");
        return;
    }

    char supplierName[50];
    printf("Enter the supplier name to search: ");
  if( scanf(" %49[^\n]", supplierName)!=3);

    sortProductsBySupplier();

    Product key = { 0 };  
    key.supplierName = supplierName;

    Product* keyPtr = &key;  

    Product** foundProduct = (Product**)bsearch(
        &keyPtr,
        productManager->products,
        productManager->productCount,
        sizeof(Product*),
        compareProductsBySupplier
    );

    if (foundProduct && *foundProduct) {
        printf("Product found:\n");
        printProduct(*foundProduct);
    }
    else {
        printf("No product found with the supplier name '%s'.\n", supplierName);
    }
}
void searchProductsByBrand() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products available to search.\n");
        return;
    }

    char brandName[50];
    printf("Enter the brand name to search: ");
    if (scanf(" %49[^\n]", brandName) != 1) {
    }
        sortProductsByBrand();

    Product key = { 0 };  
    key.brandName = brandName;

    Product* keyPtr = &key;  
    Product** foundProduct = (Product**)bsearch(
        &keyPtr,
        productManager->products,
        productManager->productCount,
        sizeof(Product*),
        compareProductsByBrand
    );

    if (foundProduct && *foundProduct) {
        printf("Product found:\n");
        printProduct(*foundProduct);
    }
    else {
        printf("No product found with the brand name '%s'.\n", brandName);
    }
}
void searchProductsByCategory() {
    ProductManager* productManager = starterProductManager();
    if (!productManager || productManager->productCount == 0) {
        printf("No products available to search.\n");
        return;
    }

    char categoryName[50];
    printf("Enter the category name to search: ");
    if (scanf(" %49[^\n]", categoryName) != 1) {

   }

    sortProductsByCategory();
    Product key = { 0 };  
    key.categoryName = categoryName;

    Product* keyPtr = &key;  
    Product** foundProduct = (Product**)bsearch(
        &keyPtr,
        productManager->products,
        productManager->productCount,
        sizeof(Product*),
        compareProductsByCategory
    );

    if (foundProduct && *foundProduct) {
        printf("Product found:\n");
        printProduct(*foundProduct);
    }
    else {
        printf("No product found in the category '%s'.\n", categoryName);
    }
}
void addProducts() {
    ProductManager* productManager = starterProductManager();
    BrandManager* brandManager = starterBrandManager();
    CategoryManager* categoryManager = starterCategoryManager();
    SupplierManager* supplierManager = starterSupplierManager();

    if (!productManager || !brandManager || !categoryManager || !supplierManager) {
        fprintf(stderr, "Error: One or more managers are NULL\n");
        return;
    }

    char name[50];
    char* description = NULL;
    int productID;
    double price;
    int validInput = 0;
    name[sizeof(name) - 1] = '\0';
    printf("\n=== Add Product ===\n");

    do {
        printf("Enter product name (max 50 characters): ");
        if (scanf(" %49[^\n]", name) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
        }
        else if (strlen(name) == 0) {
            printf("Error: Name cannot be empty.\n");
        }
        else {
            validInput = 1;
        }
    } while (!validInput);
    validInput = 0;
    clearInputBuffer();

    do {
        printf("Enter product ID (integer): ");
        if (scanf("%d", &productID) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
        }
        else if (findProductInManager(productManager, productID)) {
            printf("Error: Product ID already exists, please choose another ID.\n");
        }
        else {
            validInput = 1;
        }
    } while (!validInput);
    validInput = 0;
    clearInputBuffer();

    char tempDescription[100];
    tempDescription[sizeof(tempDescription) - 1] = '\0';
    printf("Enter product description: ");
    if (scanf(" %99[^\n]", tempDescription) == 1) {
        description = (char*)malloc((strlen(tempDescription) + 1) * sizeof(char));
        if (description == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for product description\n");
            return;
        }
        strcpy(description, tempDescription);
    }
    clearInputBuffer();

    do {
        printf("Enter product price: ");
        if (scanf("%lf", &price) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
        }
        else if (price < 0) {
            printf("Error: Price cannot be negative.\n");
        }
        else {
            validInput = 1;
        }
    } while (!validInput);
    validInput = 0;
    clearInputBuffer();

    Date manufactureDate;
    do {
        printf("Enter manufacture date (yyyy-mm-dd): ");
        if (scanf("%d-%d-%d", &manufactureDate.year, &manufactureDate.month, &manufactureDate.day) != 3) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
        }
        else if (!isValidDate(manufactureDate.day, manufactureDate.month, manufactureDate.year)) {
            printf("Error: Invalid date. Please enter a valid date.\n");
        }
        else {
            validInput = 1;
        }
    } while (!validInput);
    clearInputBuffer();

    Brand* selectedBrand = NULL;
    int choice;
    do {
        printf("\nSelect an existing brand or create a new one:\n");
        printShortBrandManager(brandManager);
        printf("\n0. Create a new brand\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1 || choice < 0 || choice > brandManager->brandCount) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
            continue;
        }

        if (choice == 0) {
            addBrands();
            selectedBrand = brandManager->brands[brandManager->brandCount - 1];
        }
        else {
            selectedBrand = brandManager->brands[choice - 1];
        }
        validInput = 1;
    } while (!validInput);
    validInput = 0;
    clearInputBuffer();

    Category* selectedCategory = NULL;
    do {
        printf("\nSelect an existing category or create a new one:\n");
        printShortCategoryManager(categoryManager);
        printf("\n0. Create a new category\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1 || choice < 0 || choice > categoryManager->categoryCount) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
            continue;
        }

        if (choice == 0) {
            addCategorys();
            selectedCategory = categoryManager->categories[categoryManager->categoryCount - 1];
        }
        else {
            selectedCategory = categoryManager->categories[choice - 1];
        }
        validInput = 1;
    } while (!validInput);
    validInput = 0;
    clearInputBuffer();

    Supplier* selectedSupplier = NULL;
    do {
        printf("\nSelect an existing supplier or create a new one:\n");
        printShortSupplierManager(supplierManager);
        printf("\n0. Create a new supplier\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1 || choice < 0 || choice > supplierManager->size) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
            continue;
        }

        if (choice == 0) {
            addSuppliers();
            selectedSupplier = supplierManager->suppliers[supplierManager->size - 1];
        }
        else {
            selectedSupplier = supplierManager->suppliers[choice - 1];
        }
        validInput = 1;
    } while (!validInput);
    clearInputBuffer();
    if (selectedBrand == NULL) {
        printf("Error: selectedBrand is NULL.\n");
        return; 
    }

    Product* newProduct = createProduct(name, description, productID, price, manufactureDate, selectedBrand->name, selectedCategory->name, selectedSupplier->companyName);
    if (newProduct) {
        addProductToManager(productManager, newProduct);
        addProductToBrand(selectedBrand, newProduct);
        addProductToCategory(selectedCategory, newProduct);
        addProductToSupplier(selectedSupplier, newProduct);
        PRINT_INFO("Adding a new product: %s", newProduct->name);
    }
    else {
        fprintf(stderr, "Failed to add product. Please try again!\n");
    }

    free(description); 
}
void addCategorys() {
    CategoryManager* categoryManager = starterCategoryManager(); 
    if (!categoryManager) {
        fprintf(stderr, "Error: Category manager is NULL\n");
        return;
    }

    char* name = NULL;
    int validInput = 0;

    printf("\n=== Add Category ===\n");
    char tempName[50];
    tempName[sizeof(tempName) - 1] = '\0';
    do {
        printf("Enter category name (max 50 characters): ");
        if (scanf(" %49[^\n]", tempName) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer(); 
        }
        else if (tempName != NULL && strlen(tempName) == 0) {
            printf("Error: Name cannot be empty.\n");
        }
        else if (findCategory(categoryManager, tempName)) { 
            printf("Error: Category name already exists. Please choose a different name.\n");
        }
        else {
            name = (char*)malloc((strlen(tempName) + 1) * sizeof(char));
            if (name == NULL) {
                fprintf(stderr, "Error: Memory allocation failed for category name\n");
                return;
            }
            strcpy(name, tempName);
            validInput = 1;
        }
    } while (!validInput);
    clearInputBuffer();
    Category* newCategory = createCategory(name);
    if (newCategory) {
        addCategory(categoryManager, newCategory); 
        printCategory(newCategory);
        printf("Category successfully added!\n");
    }
    else {
        fprintf(stderr, "Failed to add category. Please try again!\n");
    }

    free(name); 
}
void addSuppliers() {
    SupplierManager* supplierManager = starterSupplierManager(); 

    if (!supplierManager) {
        fprintf(stderr, "Error: Supplier manager is NULL\n");
        return;
    }
   

    char* companyName = NULL;
    char phone[20];
    Address* address = NULL;
    int validInput = 0;

    printf("\n=== Add Supplier ===\n");

    char tempCompanyName[50];
    tempCompanyName[sizeof(tempCompanyName) - 1] = '\0';

    do {
        printf("Enter supplier company name (max 50 characters): ");
        if (scanf(" %49[^\n]", tempCompanyName) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer(); 
        }
        else if (strlen(tempCompanyName) == 0) {
            printf("Error: Company name cannot be empty.\n");
        }
        else if (findSupplier(supplierManager, tempCompanyName)) { 
            printf("Error: Supplier name already exists. Please choose a different name.\n");
        }
        else {
            companyName = (char*)malloc((strlen(tempCompanyName) + 1) * sizeof(char));
            if (companyName == NULL) {
                fprintf(stderr, "Error: Memory allocation failed for company name\n");
                return;
            }
            strcpy(companyName, tempCompanyName);
            validInput = 1;
        }
    } while (!validInput);
    validInput = 0;
    clearInputBuffer(); 
    printf("Enter supplier phone number: ");
    if (scanf(" %19[^\n]", phone) != 1) {
        printf("Error: Invalid input format.\n");
    }
    clearInputBuffer(); 

    char street[100], city[50];
    int postalCode;
    printf("Enter supplier address details:\n");
    printf("Street: ");
    if (scanf(" %99[^\n]", street) != 1) {}
        clearInputBuffer();
    printf("City: ");
    if (scanf(" %49[^\n]", city) != 1){
    }
    clearInputBuffer();
    printf("Postal Code: ");
    if (scanf("%d", &postalCode) != 1) {
        printf("Error: Invalid input format for postal code.\n");
        clearInputBuffer();
    }

    address = createAddress(street, city, postalCode);
    Supplier* newSupplier = createSupplier(companyName, phone, *address); 
    if (newSupplier) {
        addSupplier(supplierManager, newSupplier); 
        printSupplier(newSupplier); 
        printf("Supplier successfully added!\n");
    }
    else {
        fprintf(stderr, "Failed to add supplier. Please try again!\n");
    }

    free(companyName);
}
void addOrders() {
    OrderManager* orderManager = starterOrderManager();
    CustomerManager* customerManager = starterCustomerManager();
    ProductManager* productManager = starterProductManager();

    if (!orderManager || !customerManager || !productManager) {
        fprintf(stderr, "Error: One or more managers are NULL\n");
        return;
    }

    int orderID;
    int validInput = 0;
    Customer* selectedCustomer = NULL;

    printf("\n=== Add Order ===\n");

    do {
        printf("Enter order ID (integer): ");
        if (scanf("%d", &orderID) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
        }
        else if (findOrder(orderManager, orderID)) {
            printf("Error: Order ID already exists, please choose another ID.\n");
        }
        else {
            validInput = 1;
        }
    } while (!validInput);
    validInput = 0;
    clearInputBuffer();

    int customerIndex;
    do {
        printf("\nSelect an existing customer or create a new one:\n");
        printShortCustomerManager(customerManager); 
        printf("0. Create a new customer\n");
        printf("Enter your choice (e.g., 1 for the first customer, 0 to create a new one): ");
        if (scanf("%d", &customerIndex) != 1 || customerIndex < 0) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
            continue;
        }

        if (customerIndex == 0) {
            addCustomers(); 
            selectedCustomer = customerManager->tail->data; 
        }
        else {
            selectedCustomer = getCustomerByIndex(customerManager, customerIndex - 1);
            if (!selectedCustomer) {
                printf("Error: Customer not found.\n");
            }
            else {
                validInput = 1;
            }
        }
    } while (!selectedCustomer); 

    Date orderDate;
    do {
        printf("Enter order date (yyyy-mm-dd): ");
        if (scanf("%d-%d-%d", &orderDate.year, &orderDate.month, &orderDate.day) != 3) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
        }
        else if (!isValidDateForOrder(orderDate.day, orderDate.month, orderDate.year)) {
            printf("Error: Invalid date. Please enter a valid date.\n");
        }
        else {
            validInput = 1;
        }
    } while (!validInput);
    clearInputBuffer();

    Product** orderedProducts = NULL;
    int numOfProducts = 0;
    char addMore = 'y';

    do {
        printf("\nSelect an existing product or create a new one:\n");
        printShortProductManager(productManager); 
        printf("0. Create a new product\n");
        int productIndex;
        printf("Enter your choice (e.g., 1 for the first product, 0 to create a new one): ");
        if (scanf("%d", &productIndex) != 1 || productIndex < 0) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
            continue;
        }

        Product* selectedProduct = NULL;
        if (productIndex == 0) {
            addProducts();
            selectedProduct = productManager->products[productManager->productCount - 1]; 
            if (selectedProduct) {
                printf("Newly created product: %s\n", selectedProduct->name);
            }
        }
        else {
            selectedProduct = productManager->products[productIndex - 1]; 
        }

        if (selectedProduct) {
            printf("Selected product: %s\n", selectedProduct->name);
            Product** temp = (Product**)realloc(orderedProducts, (numOfProducts + 1) * sizeof(Product*));
            if (!temp) {
                fprintf(stderr, "Memory allocation failed for orderedProducts\n");
                free(orderedProducts);
                return;
            }
            orderedProducts = temp;
            orderedProducts[numOfProducts] = selectedProduct;
            numOfProducts++;
        }
        else {
            printf("Error: Product not found.\n");
        }

        printf("Do you want to add another product? (y/n): ");
        if (scanf(" %c", &addMore) != 1) {
        }
        clearInputBuffer();
    } while (tolower(addMore) == 'y');

    if (numOfProducts > 0) {
        Order* newOrder = createOrder(orderID, selectedCustomer, orderDate);
        if (newOrder) {
            newOrder->orderedProducts = orderedProducts;
            newOrder->numOfProducts = numOfProducts;
            addOrder(orderManager, newOrder);
            printOrder(newOrder);
            printf("Order successfully added!\n");
        }
        else {
            fprintf(stderr, "Failed to add order. Please try again!\n");
            free(orderedProducts);
        }
    }
    else {
        printf("No products were added to the order.\n");
        free(orderedProducts);
    }
}
void addCustomers() {
    CustomerManager* customerManager = starterCustomerManager(); 

    if (!customerManager) {
        fprintf(stderr, "Error: Customer manager is NULL\n");
        return;
    }
    

    char* name = NULL;
    char email[100];
    int customerID;
    int validInput = 0;

    printf("\n=== Add Customer ===\n");
    char tempName[50];
    tempName[sizeof(tempName) - 1] = '\0';
    do {
        printf("Enter customer name (max 50 characters): ");
        if (scanf(" %49[^\n]", tempName) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer(); 
        }
        else if (strlen(tempName) == 0) {
            printf("Error: Name cannot be empty.\n");
        }
        else {
            name = (char*)malloc((strlen(tempName) + 1) * sizeof(char));
            if (name == NULL) {
                fprintf(stderr, "Error: Memory allocation failed for customer name\n");
                return;
            }
            strcpy(name, tempName);
            validInput = 1;
        }
    } while (!validInput);
    validInput = 0;
    clearInputBuffer(); 
    do {
        printf("Enter customer ID (integer): ");
        if (scanf("%d", &customerID) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
        }
        else if (findCustomer(customerManager, customerID)) { 
            printf("Error: Customer ID already exists, please choose another ID.\n");
        }
        else {
            validInput = 1;
        }
    } while (!validInput);
    validInput = 0;
    clearInputBuffer(); 
    printf("Enter customer email: ");
    if (scanf(" %99[^\n]", email) != 1) {
        printf("Error: Invalid input format.\n");
    }
    clearInputBuffer(); 
    Address* address = NULL;
    char street[100], city[50];
    int postalCode;
    printf("Enter customer address details:\n");
    printf("Street: ");
   if( scanf(" %99[^\n]", street)!=1);
    clearInputBuffer();
    printf("City: ");
    if(scanf(" %49[^\n]", city)!=1);
    clearInputBuffer();
    printf("Postal Code: ");
    if (scanf("%d", &postalCode) != 1) {
        printf("Error: Invalid input format for postal code.\n");
        clearInputBuffer();
    }
    clearInputBuffer();
    address = createAddress(street, city, postalCode);

    Customer* newCustomer = createCustomer(name, email, customerID, address);
    if (newCustomer) {
        addCustomer(customerManager, newCustomer);
        printCustomer(newCustomer); 
        printf("Customer successfully added!\n");
    }
    else {
        fprintf(stderr, "Failed to add customer. Please try again!\n");
    }

    free(name); 
}
void addBrands()
{
    BrandManager* brandManager = starterBrandManager(); 
    if (!brandManager) {
        fprintf(stderr, "Error: Brand manager is NULL\n");
        return;
    }

    char* name = NULL;
    int validInput = 0;

    printf("\n=== Add Brand ===\n");

    char tempName[50];
    tempName[sizeof(tempName) - 1] = '\0';
    do {
        printf("Enter brand name (max 50 characters): ");
        if (scanf(" %49[^\n]", tempName) != 1) {
            printf("Error: Invalid input format.\n");
            clearInputBuffer();
        }
        else if (strlen(tempName) == 0) {
            printf("Error: Name cannot be empty.\n");
        }
        else if (findBrand(brandManager, tempName)) {
            printf("Error: Brand name already exists. Please choose a different name.\n");
        }
        else {
            name = (char*)malloc((strlen(tempName) + 1) * sizeof(char));
            if (name == NULL) {
                fprintf(stderr, "Error: Memory allocation failed for brand name\n");
                return;
            }
            strcpy(name, tempName);
            validInput = 1;
        }
    } while (!validInput);
    clearInputBuffer();

    Brand* newBrand = createBrand(name);
    if (newBrand) {
        addBrand(brandManager, newBrand);
        printBrand(newBrand);
        printf("Brand successfully added!\n");
    }
    else {
        fprintf(stderr, "Failed to add brand. Please try again!\n");
    }

    free(name);
}
void updateProducts() {
    ProductManager* productManager = starterProductManager();
    OrderManager* orderManager = starterOrderManager();
    CategoryManager* categoryManager = starterCategoryManager();
    BrandManager* brandManager = starterBrandManager();
    SupplierManager* supplierManager = starterSupplierManager();

    if (!productManager || productManager->productCount == 0) {
        printf("No products available to update.\n");
        return;
    }

    printf("\n=== Update a Product ===\n");
    printShortProductManager(productManager);

    int choice;
    printf("Enter the number of the product to update (1 to %d): ", productManager->productCount);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > productManager->productCount) {
        printf("Invalid choice. Aborting update.\n");
        clearInputBuffer();
        return;
    }

    Product* productToUpdate = productManager->products[choice - 1];

    if (isProductInAnyOrder(orderManager, productToUpdate) == 1) {
        printf("This product is part of an existing order and cannot be updated.\n");
        return;
    }

    printf("\nCurrent details of the product:\n");
    printProduct(productToUpdate);

    char newName[50], newDescription[100], newBrandName[50], newCategoryName[50], newSupplierName[50];
    double newPrice;
    Date newManufactureDate;
    int validInput = 0;

    printf("\nEnter new product name (or press Enter to keep current): ");
    fgets(newName, 50, stdin);
    if (newName[0] != '\n') { 
        newName[strcspn(newName, "\n")] = '\0'; 
        strcpy(productToUpdate->name, newName);
    }
    printf("Enter new description (or press Enter to keep current): ");
    fgets(newDescription, 100, stdin);
    if (newDescription[0] != '\n') { 
        newDescription[strcspn(newDescription, "\n")] = '\0';
        strcpy(productToUpdate->description, newDescription);
    }
    printf("Enter new brand name (or press Enter to keep current): ");
    fgets(newBrandName, 50, stdin);
    if (newBrandName[0] != '\n') { 
        newBrandName[strcspn(newBrandName, "\n")] = '\0'; 
        Brand* selectedBrand = NULL;
        int brandChoice;
        do {
            printf("\nSelect an existing brand or create a new one:\n");
            printShortBrandManager(brandManager);
            printf("\n0. Create a new brand\n");
            printf("Enter your choice: ");
            if (scanf("%d", &brandChoice) != 1 || brandChoice < 0 || brandChoice > brandManager->brandCount) {
                printf("Error: Invalid input format.\n");
                clearInputBuffer();
                continue;
            }

            if (brandChoice == 0) {
                addBrands();
                selectedBrand = brandManager->brands[brandManager->brandCount - 1];
            }
            else {
                selectedBrand = brandManager->brands[brandChoice - 1];
            }
            validInput = 1;
        } while (!validInput);
        validInput = 0;
        clearInputBuffer();

        strcpy(productToUpdate->brandName, selectedBrand->name);
    }

    printf("Enter new category name (or press Enter to keep current): ");
    fgets(newCategoryName, 50, stdin);
    if (newCategoryName[0] != '\n') { 
        newCategoryName[strcspn(newCategoryName, "\n")] = '\0'; 
        Category* selectedCategory = NULL;
        int categoryChoice;
        do {
            printf("\nSelect an existing category or create a new one:\n");
            printShortCategoryManager(categoryManager);
            printf("\n0. Create a new category\n");
            printf("Enter your choice: ");
            if (scanf("%d", &categoryChoice) != 1 || categoryChoice < 0 || categoryChoice > categoryManager->categoryCount) {
                printf("Error: Invalid input format.\n");
                clearInputBuffer();
                continue;
            }

            if (categoryChoice == 0) {
                addCategorys();
                selectedCategory = categoryManager->categories[categoryManager->categoryCount - 1];
            }
            else {
                selectedCategory = categoryManager->categories[categoryChoice - 1];
            }
            validInput = 1;
        } while (!validInput);
        validInput = 0;
        clearInputBuffer();

        strcpy(productToUpdate->categoryName, selectedCategory->name);
    }
    printf("Enter new supplier name (or press Enter to keep current): ");
    fgets(newSupplierName, 50, stdin);
    if (newSupplierName[0] != '\n') { 
        newSupplierName[strcspn(newSupplierName, "\n")] = '\0'; 
        Supplier* selectedSupplier = NULL;
        int supplierChoice;
        do {
            printf("\nSelect an existing supplier or create a new one:\n");
            printShortSupplierManager(supplierManager);
            printf("\n0. Create a new supplier\n");
            printf("Enter your choice: ");
            if (scanf("%d", &supplierChoice) != 1 || supplierChoice < 0 || supplierChoice > supplierManager->size) {
                printf("Error: Invalid input format.\n");
                clearInputBuffer();
                continue;
            }

            if (supplierChoice == 0) {
                addSuppliers();
                selectedSupplier = supplierManager->suppliers[supplierManager->size - 1];
            }
            else {
                selectedSupplier = supplierManager->suppliers[supplierChoice - 1];
            }
            validInput = 1;
        } while (!validInput);
        clearInputBuffer();

        strcpy(productToUpdate->supplierName, selectedSupplier->companyName);
    }

    printf("Enter new price (or -1 to keep current): ");
    if (scanf("%lf", &newPrice) == 1 && newPrice >= 0) {
        productToUpdate->price = newPrice;
    }

    printf("Enter new manufacture date (yyyy-mm-dd, or press Enter to keep current): ");
    char dateInput[20];
    fgets(dateInput, 20, stdin);
    if (strlen(dateInput) > 1) { 
        if(scanf(dateInput, "%d-%d-%d", &newManufactureDate.year, &newManufactureDate.month, &newManufactureDate.day)!=3){}
        if (isValidDate(newManufactureDate.day, newManufactureDate.month, newManufactureDate.year)) {
            productToUpdate->manufactureDate = newManufactureDate;
        }
    }
    for (int i = 0; i < categoryManager->categoryCount; i++) {
        Category* category = categoryManager->categories[i];
        for (int j = 0; j < category->productCount; j++) {
            if (category->products[j]->productID == productToUpdate->productID) {
                category->products[j] = productToUpdate;
            }
        }
    }

    for (int i = 0; i < brandManager->brandCount; i++) {
        Brand* brand = brandManager->brands[i];
        for (int j = 0; j < brand->productCount; j++) {
            if (brand->products[j]->productID == productToUpdate->productID) {
                brand->products[j] = productToUpdate;
            }
        }
    }

    for (int i = 0; i < supplierManager->size; i++) {
        Supplier* supplier = supplierManager->suppliers[i];
        for (int j = 0; j < supplier->numOfProducts; j++) {
            if (supplier->suppliedProducts[j]->productID == productToUpdate->productID) {
                supplier->suppliedProducts[j] = productToUpdate;
            }
        }
    }

    printf("Product updated successfully.\n");
}
void deleteProducts() {
    ProductManager* productManager = starterProductManager();
    OrderManager* orderManager = starterOrderManager();
    CategoryManager* categoryManager = starterCategoryManager();
    BrandManager* brandManager = starterBrandManager();
    SupplierManager* supplierManager = starterSupplierManager();

    if (!productManager || productManager->productCount == 0) {
        printf("No products available to delete.\n");
        return;
    }

    printf("\n=== Delete a Product ===\n");
    printShortProductManager(productManager);

    int choice;
    printf("Enter the number of the product to delete (1 to %d): ", productManager->productCount);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > productManager->productCount) {
        printf("Invalid choice. Aborting deletion.\n");
        clearInputBuffer();
        return;
    }

    Product* productToDelete = productManager->products[choice - 1];

    if (isProductInAnyOrder(orderManager, productToDelete) == 1) {
        printf("This product is part of an existing order and cannot be deleted.\n");
        return;
    }

    for (int i = 0; i < categoryManager->categoryCount; i++) {
        Category* category = categoryManager->categories[i];
        for (int j = 0; j < category->productCount; j++) {
            if (category->products[j] == productToDelete) {
                for (int k = j; k < category->productCount - 1; k++) {
                    category->products[k] = category->products[k + 1];
                }
                category->productCount--;
                Product** temp = realloc(category->products, category->productCount * sizeof(Product*));
                if (temp != NULL) {
                    category->products = temp;
                }
                else {
                    printf("Error reallocating memory.\n");
                }
                break;
            }
        }
    }

    for (int i = 0; i < brandManager->brandCount; i++) {
        Brand* brand = brandManager->brands[i];
        for (int j = 0; j < brand->productCount; j++) {
            if (brand->products[j] == productToDelete) {
                for (int k = j; k < brand->productCount - 1; k++) {
                    brand->products[k] = brand->products[k + 1];
                }
                brand->productCount--;
                Product** temp = realloc(brand->products, brand->productCount * sizeof(Product*));
                if (temp != NULL) {
                    brand->products = temp;
                }
                else {
                    printf("Error reallocating memory for suppliedProducts.\n");
                }
                break;
            }
        }
    }
    for (int i = 0; i < supplierManager->size; i++) {
        Supplier* supplier = supplierManager->suppliers[i];
        for (int j = 0; j < supplier->numOfProducts; j++) {
            if (supplier->suppliedProducts[j] == productToDelete) {
                for (int k = j; k < supplier->numOfProducts - 1; k++) {
                    supplier->suppliedProducts[k] = supplier->suppliedProducts[k + 1];
                }
                supplier->numOfProducts--;
                Product** temp = realloc(supplier->suppliedProducts, supplier->numOfProducts * sizeof(Product*));
                if (temp != NULL) {
                    supplier->suppliedProducts = temp;
                }
                else {
                    printf("Error reallocating memory for suppliedProducts.\n");
                }          
                break;
            }
        }
    }

    deleteProductFromManager(productManager, productToDelete->productID);

    printf("Product deleted successfully.\n");
}
void deleteCategorys() {
    CategoryManager* categoryManager = starterCategoryManager();
    OrderManager* orderManager = starterOrderManager();

    if (!categoryManager || categoryManager->categoryCount == 0) {
        printf("No categories available to delete.\n");
        return;
    }

    printf("\n=== Delete a Category ===\n");
    printShortCategoryManager(categoryManager);

    int choice;
    printf("Enter the number of the category to delete (1 to %d): ", categoryManager->categoryCount);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > categoryManager->categoryCount) {
        printf("Invalid choice. Aborting deletion.\n");
        clearInputBuffer();
        return;
    }

    Category* categoryToDelete = categoryManager->categories[choice - 1];

    if (isCategoryInAnyOrder(orderManager, categoryToDelete->name) == 1) {
        printf("This category is part of an existing order and cannot be deleted.\n");
        return;
    }

    deleteCategoryFromManager(categoryManager, categoryToDelete->name);

    printf("Category deleted successfully.\n");
}
void deleteSuppliers() {
    SupplierManager* supplierManager = starterSupplierManager();
    OrderManager* orderManager = starterOrderManager();

    if (!supplierManager || supplierManager->size == 0) {
        printf("No suppliers available to delete.\n");
        return;
    }

    printf("\n=== Delete a Supplier ===\n");
    printShortSupplierManager(supplierManager);

    int choice;
    printf("Enter the number of the supplier to delete (1 to %d): ", supplierManager->size);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > supplierManager->size) {
        printf("Invalid choice. Aborting deletion.\n");
        clearInputBuffer();
        return;
    }

    Supplier* supplierToDelete = supplierManager->suppliers[choice - 1];

    if (isSupplierInAnyOrder(orderManager, supplierToDelete->companyName) == 1) {
        printf("This supplier is part of an existing order and cannot be deleted.\n");
        return;
    }

    deleteSupplier(supplierManager, supplierToDelete->companyName);

    printf("Supplier deleted successfully.\n");
}
void deleteCustomers() {
    CustomerManager* customerManager = starterCustomerManager();
    OrderManager* orderManager = starterOrderManager();

    if (!customerManager || !customerManager->head) {
        printf("No customers available to delete.\n");
        return;
    }

    printf("\n=== Delete a Customer ===\n");
    printCustomerManager(customerManager);

    int choice;
    printf("Enter the number of the customer to delete (1 for the first customer, etc.): ");
    if (scanf("%d", &choice) != 1 || choice < 1) {
        printf("Invalid choice. Aborting deletion.\n");
        clearInputBuffer();
        return;
    }

    Customer* customerToDelete = getCustomerByIndex(customerManager, choice - 1);

    if (isCustomerInAnyOrder(orderManager, customerToDelete) == 1) {
        printf("This customer is part of an existing order and cannot be deleted.\n");
        return;
    }

    deleteCustomer(customerManager, customerToDelete->customerID);

    printf("Customer deleted successfully.\n");
}
void deleteBrands() {
    BrandManager* brandManager = starterBrandManager();
    OrderManager* orderManager = starterOrderManager();

    if (!brandManager || brandManager->brandCount == 0) {
        printf("No brands available to delete.\n");
        return;
    }

    printf("\n=== Delete a Brand ===\n");
    printShortBrandManager(brandManager);

    int choice;
    printf("Enter the number of the brand to delete (1 to %d): ", brandManager->brandCount);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > brandManager->brandCount) {
        printf("Invalid choice. Aborting deletion.\n");
        clearInputBuffer();
        return;
    }

    Brand* brandToDelete = brandManager->brands[choice - 1];

    if (isBrandInAnyOrder(orderManager, brandToDelete->name) == 1) {
        printf("This brand is part of an existing order and cannot be deleted.\n");
        return;
    }

    deleteBrandFromManager(brandManager, brandToDelete->name);

    printf("Brand deleted successfully.\n");
}
void deleteOrders() {
    OrderManager* orderManager = starterOrderManager();
    if (!orderManager || orderManager->size == 0) {
        printf("No orders available to delete.\n");
        return;
    }

    printf("\n=== Delete an Order ===\n");
    printOrderManager(orderManager);
    if (orderManager->size <= 0) {
        printf("Invalid number of orders.\n");
        return;
    }

    int choice;
    printf("Enter the number of the order to delete (1 to %d): ", orderManager->size);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > orderManager->size) {
        printf("Invalid choice. Aborting deletion.\n");
        clearInputBuffer();
        return;
    }

    OrderNode* current = orderManager->head;
    OrderNode* previous = NULL;
    int index = 1;

    while (current && index < choice) {
        previous = current;
        current = current->next;
        index++;
    }

    if (current) {
        if (previous) {
            previous->next = current->next;
        }
        else {
            orderManager->head = current->next;
        }
        deleteOrder(orderManager, current->data->orderID); 
        printf("Order deleted successfully.\n");
    }
    else {
        printf("Error: Could not find the selected order.\n");
    }
}
void displayProducts()
{
    ProductManager* productManager = starterProductManager();
    printf("\n=== Products ===\n");
    if (!productManager || productManager->productCount == 0) {
        printf("\nNo products available.\n");
        return;
    }
    printProductManager(productManager);

}
void displayCustomers()
{
    CustomerManager* customerManager = starterCustomerManager();
    printf("\n=== Customers ===\n");
    if (!customerManager || !customerManager->head) {
        printf("\nNo customers available.\n");
        return;
    }
    printCustomerManager(customerManager);
}
void displaySuppliers()
{
    SupplierManager* supplierManager = starterSupplierManager();
    printf("\n=== Suppliers ===\n");
    if (!supplierManager || supplierManager->size == 0) {
        printf("\nNo suppliers available.\n");
        return;
    }
    printSupplierManager(supplierManager);
}
void displayOrders()
{
    OrderManager* orderManager = starterOrderManager();
    printf("\n=== Orders ===\n");
    if (!orderManager || orderManager->head == NULL) {
        printf("\nNo orders available.\n");
        return;
    }
    printOrderManager(orderManager);

}
void displayBrands()
{
    BrandManager* brandManager = starterBrandManager();
    printf("\n=== Brands ===\n");
    if (!brandManager || brandManager->brandCount == 0) {
        printf("\nNo brands available.\n");
        return;
    }
    printBrandManager(brandManager);
}
void displayCategorys()
{
    CategoryManager* categoryManager = starterCategoryManager();
    printf("\n=== Categorys ===\n");
    if (!categoryManager || categoryManager->categoryCount == 0) {
        printf("\nNo categorys available.\n");
        return;
    }
    printCategoryManager(categoryManager);

}
void displaySystem() {
        printf("\n========================\n");
        printf("   SYSTEM OVERVIEW\n");
        printf("========================\n");

        printf("\n************************\n");
        displayProducts();
        printf("\n========================\n");

        printf("\n************************\n");
        displayCustomers();
        printf("\n========================\n");

        printf("\n************************\n");
        displaySuppliers();
        printf("\n========================\n");

        printf("\n************************\n");
        displayOrders();
        printf("\n========================\n");

        printf("\n************************\n");
        displayBrands();
        printf("\n========================\n");

        printf("\n************************\n");
        displayCategorys();
        printf("\n========================\n");

        printf("   END OF SYSTEM OVERVIEW\n");
        printf("========================\n");
    }
