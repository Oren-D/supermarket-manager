Submitted by:

Oren Davidian - 315871210
Andrei Tarkhanov - 336104575
About the System:
This project involves creating a management system for a clothing store. The system enables the user to manage products, customers, suppliers, brands, and categories through intuitive and simple operations. Users can load data from textual or binary files, add, update, and delete records, and perform searches and sorting based on various criteria.

The system also supports order management, associating products with customers and suppliers. It ensures automatic data saving to files for future use and retrieval.

System Structure:
1. Product
Description: Represents a product in the store.
Fields:
Product ID
Name
Description
Price
Manufacture Date
Brand Name
Category Name
Supplier Name
2. Customer
Description: Represents a customer.
Fields:
Name
Email
Address
3. Supplier
Description: Represents a supplier.
Fields:
Company Name
Phone
Address
Supplied Products (Array)
Number of Products
4. Brand
Description: Represents a brand.
Fields:
Name
Associated Products (Array)
Number of Products
5. Category
Description: Represents a category.
Fields:
Name
Associated Products (Array)
Number of Products
6. Address
Description: Represents an address.
Fields:
Street
City
Postal Code
7. Order
Description: Represents a customer order.
Fields:
Order ID
Customer (Pointer to Customer)
Order Date
Ordered Products (Array)
Number of Products
Managers:
These components are responsible for managing the system's entities. For example:

ProductManager: Handles adding, removing, and updating products.
CustomerManager: Manages a linked list of customers.
SupplierManager: Manages an array of suppliers.
Key Functionalities:
1. Save and Load System:
Save all system data (products, customers, suppliers, etc.) to a text or binary file.
Load data to restore the system's state from saved files.
2. Operations Available:
Add, Update, or Delete Products
Manage Categories, Brands, and Suppliers
Create and View Orders
Search Functionality: Enables searching for products, customers, or orders.
Example Stored Data Format:
Data is saved sequentially for different entities (e.g., products, categories) with all relevant fields to ensure easy future retrieval.

