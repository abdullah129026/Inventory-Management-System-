[README.md](https://github.com/user-attachments/files/26340963/README.md)
# Inventory Management System

A comprehensive console-based inventory management system built in C++ that provides complete CRUD operations for product management, inventory tracking, and report generation.

## Features

### Core Functionality
- **Product Management**
  - Add new products with ID, name, price, quantity, and category
  - Remove existing products by ID
  - Update product details
  - Search products by ID or name

- **Inventory Operations**
  - Restock products (increase quantity)
  - Sell products (decrease quantity with stock validation)
  - View all products in inventory
  - Sort products by price (ascending) or quantity (descending)

- **Data Persistence**
  - Automatic saving of all products to `products.txt`
  - Load existing data on program startup
  - Transaction logging to `transactions.txt`

- **Reports**
  - Sales Report - View all transaction records
  - Stock Report - Display current product inventory
  - Inventory Report - Summary with total products and inventory value

- **User Interface**
  - Clean, menu-driven interface
  - Screen clearing between operations
  - User-friendly prompts and confirmations
  - Cross-platform support (Windows/Linux/Mac)

## Project Structure

```
Project 5/
├── Header.h                          # Header file with class declarations
├── Inventory Managment System.cpp    # Main implementation file
├── InventorySystem.exe               # Compiled executable
├── products.txt                      # Product data storage (auto-generated)
├── transactions.txt                  # Transaction logs (auto-generated)
└── README.md                         # This file
```

## Classes Overview

### 1. Product
Represents a product in the inventory with attributes:
- `id` - Unique product identifier
- `name` - Product name
- `price` - Product price
- `quantity` - Available quantity
- `category` - Product category

### 2. Inventory
Manages the collection of products using an unordered map:
- Stores products with ID as key
- Provides search, add, remove, update operations
- Supports sorting and filtering

### 3. FileManager
Handles all file I/O operations:
- Save/load products to/from `products.txt`
- Save/load transactions to/from `transactions.txt`
- Uses absolute paths for data persistence

### 4. Transaction
Records inventory transactions:
- Tracks product ID, quantity, type, and date
- Serializes transaction data for storage

### 5. ReportGenerator
Generates various reports:
- Sales reports from transaction data
- Stock reports showing current inventory
- Inventory summary with calculated values

### 6. InventorySystem
Main application controller:
- Orchestrates all components
- Handles user interaction
- Manages program flow

## Installation & Compilation

### Requirements
- C++ compiler (g++, MinGW, or similar)
- Standard C++ libraries

### Compile on Windows
```bash
g++ "Inventory Managment System.cpp" -o InventorySystem.exe
```

### Compile on Linux/Mac
```bash
g++ "Inventory Managment System.cpp" -o InventorySystem
```

## Usage

### Running the Program
```bash
# Windows
InventorySystem.exe

# Linux/Mac
./InventorySystem
```

### Menu Options

1. **Add Product** - Enter product details (ID, name, price, quantity, category)
2. **Remove Product** - Enter product ID to remove
3. **Update Product** - Modify existing product details
4. **Search Product** - Search by ID or name
5. **Restock Product** - Add quantity to existing stock
6. **Sell Product** - Reduce quantity (validates sufficient stock)
7. **Show Reports** - Generate sales, stock, or inventory reports
8. **Exit** - Save data and exit program

### Data File Format

**products.txt** (CSV format):
```
id,name,price,quantity,category
1,Laptop,999.99,10,Electronics
2,Mouse,25.50,50,Electronics
```

**transactions.txt** (CSV format):
```
date,type,productID,quantity
2026-03-29,Sale,1,2
2026-03-29,Restock,2,20
```

## Key Features Explained

### Clear Screen Functionality
The program automatically clears the console screen between operations for a clean interface:
- Uses `system("cls")` on Windows
- Uses `system("clear")` on Linux/Mac

### Data Persistence
- All product data is automatically saved to `products.txt` when exiting
- Data is automatically loaded on program startup
- Files use absolute paths to ensure consistency across runs
- Confirmation messages show save/load status

### Input Validation
- Price must be positive
- Quantity cannot be negative
- Stock sales validated against available quantity
- Duplicate product IDs prevented

## Troubleshooting

### Data Not Persisting
- Ensure you're running the executable from the project directory
- Check that `products.txt` and `transactions.txt` have write permissions
- Verify the absolute path in FileManager constructor matches your project location

### Compilation Errors
- Ensure all required headers are included (`<algorithm>`, `<cstdlib>`)
- Check that function signatures match between header and implementation
- Verify C++11 or later standard support

### File Not Found Errors
- The program creates files automatically on first run
- If files are missing, check the absolute path in FileManager constructor
- Ensure the directory exists and is writable

## Future Enhancements

Potential improvements for the system:
- [ ] Date/time stamping for transactions
- [ ] Advanced search with filters and partial matching
- [ ] Export reports to CSV/PDF
- [ ] User authentication and multi-user support
- [ ] Low stock alerts and automatic reordering
- [ ] Graphical user interface (GUI)
- [ ] Database integration instead of flat files
- [ ] Barcode/QR code scanning support

## Technical Details

### C++ Standards Used
- C++11 or later
- STL containers: `unordered_map`, `vector`, `string`
- File I/O: `fstream`, `ifstream`, `ofstream`
- String streams: `stringstream`
- Lambda functions for sorting

### File Encoding
- Text files use UTF-8 encoding
- CSV format with comma delimiters
- One record per line

## License

This project is created for educational purposes.

## Author

Inventory Management System
Created: 2026

---

**Note**: For best results, always run the executable from the project directory to ensure proper file access and data persistence.
