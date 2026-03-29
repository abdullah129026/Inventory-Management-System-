#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

// Product class

class Product {
private:
	string name;
	int id;
	double price;
	int quantity;
    string category;
public:
    Product();
    Product(string name, int id, double price, int quantity, string category);

    // getters

    int getId() const;
    string getName() const;
    double getPrice() const;
    int getQuantity() const;
    string getCategory() const;

    //setters

    void setPrice(double);
    void setQuantity(int);

    //Methods

    void increaseStock(int);
    void decreaseStock(int);

    string serialize() const;
    void deserialize(string);
    void display() const;
};
    
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/



//Inventory class

class Inventory {
private:

    unordered_map<int, Product> products;
public:
        
    void addProduct(Product);
    void removeProduct(int id);
    void updateProduct(int id);

    Product* searchProductbyId(int id);
    vector<Product> searchProductbyName(string name);

    void reStock(int id, int quantity);
    void sellProduct(int id, int quantity);

    vector<Product> sortbyPrice();
    vector<Product> sortbyQuantity();

    unordered_map<int , Product>& getAllProducts();
    void display();
       
};

    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/

//File Manager class

class FileManager {
private:
    string ProductFile;
    string transactionFile;
public:
    
    FileManager();
    void saveProducts(unordered_map<int, Product>&);
    void loadProducts(unordered_map<int, Product>&);

    void saveTransactions(string record);
    vector<string> loadTransactions();
    
};

    /*------------------------------------------------------------*/ 
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/

//Transaction class

class Transaction {
private:
    string date;
    string type;
    int productID;
    int quantity;
public:
    Transaction();
    Transaction(int productID, int quantity, string type, string date);

    string serialize();
    void display();
   
};

    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/

//ReportGenerator class

class ReportGenerator {
private:
public:
    void SalesReport(vector<Transaction>& transactions);
    void StockReport(unordered_map<int, Product>& products);
    void InventoryReport(unordered_map<int, Product>& products);

};

    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/
    /*------------------------------------------------------------*/

//InventorySystem class

class InventorySystem {
private:
    Inventory inventory;
    FileManager fileManager;
    ReportGenerator reportGenerator;
public:
    void run();

    void addProduct();
    void removeProduct();
    void updateProduct();
    void searchProduct();
    void reStockProduct();
    void sellProduct();
    void showReport();

    void loadData();
    void saveData();

};

void clearScreen();

#endif
 