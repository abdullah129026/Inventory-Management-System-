#include"Header.h"
#include<algorithm>
#include<cstdlib>

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Product class

Product::Product()
{
    id = 0;
    name="";
    price=0;
    quantity=0;
    category="";
}
Product::Product(string name, int id, double price, int quantity, string category)
{
    this->name = name;
    this->id = id;
    this->price = price;
    this->quantity = quantity;
    this->category = category;
}
//getters
int Product::getId() const {return id;}
string Product::getName() const {return name;}
double Product::getPrice() const {return price;}
int Product::getQuantity() const {return quantity;}
string Product::getCategory() const {return category;}

//setters
void Product::setPrice(double price) {
    if(price > 0)
        this->price = price;
}
void Product::setQuantity(int quantity) {
    if(quantity >= 0)
        this->quantity = quantity;
}

void Product::increaseStock(int amount)
{
    if(amount > 0)
        quantity += amount;
}
void Product::decreaseStock(int amount)
{
    if(amount > 0)
        quantity -= amount;
    else
        cout << "Invalid amount" << endl;
}
string Product::serialize() const
{
    stringstream ss;
    ss << id << "," << name << "," << price << "," << quantity << "," << category;
    return ss.str();
}
void Product::deserialize(string data)
{
    stringstream ss(data);
    string token;
    getline(ss, token, ',');
    id = stoi(token);
    getline(ss, name, ',');
    getline(ss, token, ',');
    price = stod(token);
    getline(ss, token, ',');
    quantity = stoi(token);
    getline(ss, category, ',');
}
void Product::display() const
{
    cout << id << " | " 
         << name << " | " 
         << price << " | " 
         << quantity << " | " 
         << category << endl;
}




//Inventory class

void Inventory::addProduct(Product product){
    int id = product.getId();
    if(products.find(id) != products.end())
    {
        cout << "Product with id " << id << " already exists" << endl;
        return;
    }
    products[id] = product;
}

void Inventory::removeProduct(int id){
    if(products.erase(id))
        cout << "Product with id " << id << " removed successfully" << endl;
    else
        cout << "Product with id " << id << " does not exist" << endl;
}

void Inventory::updateProduct(int id){
    if(products.find(id) == products.end())
    {
        cout << "Product with id " << id << " does not exist" << endl;
        return;
    }
    
    string name, category;
    double price;
    int quantity;
    
    cout << "Enter new name: ";
    cin >> name;
    cout << "Enter new price: ";
    cin >> price;
    cout << "Enter new quantity: ";
    cin >> quantity;
    cout << "Enter new category: ";
    cin >> category;
    
    Product newProduct;
    newProduct.setPrice(price);
    newProduct.setQuantity(quantity);
    products[id] = newProduct;
    cout << "Product updated successfully" << endl;
}

Product* Inventory::searchProductbyId(int id){
    auto it = products.find(id);
    if(it != products.end()){
        return &(it->second);
    }
    return nullptr;
}

vector<Product> Inventory::searchProductbyName(string name){
    vector<Product> result;
    for(auto& pair : products){
        if(pair.second.getName() == name){
            result.push_back(pair.second);
        }
    }
    return result;
}

void Inventory::reStock(int id, int quantity){
    auto it = products.find(id);
    if(it != products.end()){
        it->second.increaseStock(quantity);
        cout << "Product restocked successfully" << endl;
    }
    else{
        cout << "Product with id " << id << " does not exist" << endl;
    }
}

void Inventory::sellProduct(int id, int quantity){
    auto it = products.find(id);
    if(it != products.end()){
        if(it->second.getQuantity() >= quantity){
            it->second.decreaseStock(quantity);
            cout << "Product sold successfully" << endl;
        }
        else{
            cout << "Insufficient stock" << endl;
        }
    }
    else{
        cout << "Product with id " << id << " does not exist" << endl;
    }
}

vector<Product> Inventory::sortbyPrice(){
    vector<Product> sorted;
    for(auto& pair : products){
        sorted.push_back(pair.second);
    }
    sort(sorted.begin(), sorted.end(), [](Product& a, Product& b){
        return a.getPrice() < b.getPrice();
    });
    return sorted;
}

vector<Product> Inventory::sortbyQuantity(){
    vector<Product> sorted;
    for(auto& pair : products){
        sorted.push_back(pair.second);
    }
    sort(sorted.begin(), sorted.end(), [](Product& a, Product& b){
        return a.getQuantity() > b.getQuantity();
    });
    return sorted;
}

unordered_map<int, Product>& Inventory::getAllProducts(){
    return products;
}

void Inventory::display(){
    if(products.empty()){
        cout << "No products in inventory" << endl;
        return;
    }
    for(auto& pair : products){
        pair.second.display();
    }
}


// FileManager class

FileManager::FileManager(){
    // Use absolute paths based on executable location
    string exePath = "c:\\Users\\Shahid computers\\Desktop\\C++ projects\\Project 5\\";
    ProductFile = exePath + "products.txt";
    transactionFile = exePath + "transactions.txt";
}

void FileManager::saveProducts(unordered_map<int, Product>& products){
    ofstream file(ProductFile);
    if(file.is_open()){
        for(auto& pair : products){
            file << pair.second.serialize() << endl;
        }
        file.close();
        cout << "Products saved to file successfully!" << endl;
    } else {
        cout << "Error: Could not open file for writing!" << endl;
    }
}

void FileManager::loadProducts(unordered_map<int, Product>& products){
    ifstream file(ProductFile);
    if(file.is_open()){
        string line;
        int count = 0;
        while(getline(file, line)){
            Product p;
            p.deserialize(line);
            products[p.getId()] = p;
            count++;
        }
        file.close();
        cout << "Loaded " << count << " products from file." << endl;
    } else {
        cout << "No existing data file found. Starting with empty inventory." << endl;
    }
}

void FileManager::saveTransactions(string record){
    ofstream file(transactionFile, ios::app);
    if(file.is_open()){
        file << record << endl;
        file.close();
    }
}

vector<string> FileManager::loadTransactions(){
    vector<string> transactions;
    ifstream file(transactionFile);
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            transactions.push_back(line);
        }
        file.close();
    }
    return transactions;
}


// Transaction class

Transaction::Transaction(){
    date = "";
    type = "";
    productID = 0;
    quantity = 0;
}

Transaction::Transaction(int productID, int quantity, string type, string date){
    this->productID = productID;
    this->quantity = quantity;
    this->type = type;
    this->date = date;
}

string Transaction::serialize(){
    stringstream ss;
    ss << date << "," << type << "," << productID << "," << quantity;
    return ss.str();
}

void Transaction::display(){
    cout << date << " | " << type << " | " << productID << " | " << quantity << endl;
}


// ReportGenerator class

void ReportGenerator::SalesReport(vector<Transaction>& transactions){
    cout << "\n========== SALES REPORT ==========" << endl;
    for(auto& t : transactions){
        t.display();
    }
    cout << "==================================" << endl;
}

void ReportGenerator::StockReport(unordered_map<int, Product>& products){
    cout << "\n========== STOCK REPORT ==========" << endl;
    for(auto& pair : products){
        pair.second.display();
    }
    cout << "==================================" << endl;
}

void ReportGenerator::InventoryReport(unordered_map<int, Product>& products){
    cout << "\n========== INVENTORY REPORT ==========" << endl;
    cout << "Total Products: " << products.size() << endl;
    int totalValue = 0;
    for(auto& pair : products){
        totalValue += pair.second.getPrice() * pair.second.getQuantity();
    }
    cout << "Total Inventory Value: " << totalValue << endl;
    cout << "======================================" << endl;
}


// InventorySystem class

void InventorySystem::run(){
    loadData();
    int choice;
    do{
        clearScreen();
        cout << "\n===== INVENTORY MANAGEMENT SYSTEM =====" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Remove Product" << endl;
        cout << "3. Update Product" << endl;
        cout << "4. Search Product" << endl;
        cout << "5. Restock Product" << endl;
        cout << "6. Sell Product" << endl;
        cout << "7. Show Reports" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                addProduct();
                break;
            case 2:
                removeProduct();
                break;
            case 3:
                updateProduct();
                break;
            case 4:
                searchProduct();
                break;
            case 5:
                reStockProduct();
                break;
            case 6:
                sellProduct();
                break;
            case 7:
                showReport();
                break;
            case 8:
                saveData();
                cout << "Data saved successfully!" << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }while(choice != 8);
}

void InventorySystem::addProduct(){
    clearScreen();
    int id;
    string name, category;
    double price;
    int quantity;
    
    cout << "Enter product ID: ";
    cin >> id;
    cout << "Enter product name: ";
    cin >> name;
    cout << "Enter product price: ";
    cin >> price;
    cout << "Enter product quantity: ";
    cin >> quantity;
    cout << "Enter product category: ";
    cin >> category;
    
    Product p(name, id, price, quantity, category);
    inventory.addProduct(p);
}

void InventorySystem::removeProduct(){
    clearScreen();
    int id;
    cout << "Enter product ID to remove: ";
    cin >> id;
    inventory.removeProduct(id);
}

void InventorySystem::updateProduct(){
    clearScreen();
    int id;
    cout << "Enter product ID to update: ";
    cin >> id;
    inventory.updateProduct(id);
}

void InventorySystem::searchProduct(){
    clearScreen();
    int choice;
    cout << "Search by: 1) ID  2) Name: ";
    cin >> choice;
    
    if(choice == 1){
        int id;
        cout << "Enter product ID: ";
        cin >> id;
        Product* p = inventory.searchProductbyId(id);
        if(p != nullptr){
            cout << "Product found: " << endl;
            p->display();
        }
        else{
            cout << "Product not found" << endl;
        }
    }
    else if(choice == 2){
        string name;
        cout << "Enter product name: ";
        cin >> name;
        vector<Product> results = inventory.searchProductbyName(name);
        if(!results.empty()){
            cout << "Products found:" << endl;
            for(auto& p : results){
                p.display();
            }
        }
        else{
            cout << "No products found with that name" << endl;
        }
    }
}

void InventorySystem::reStockProduct(){
    clearScreen();
    int id, quantity;
    cout << "Enter product ID: ";
    cin >> id;
    cout << "Enter quantity to add: ";
    cin >> quantity;
    inventory.reStock(id, quantity);
}

void InventorySystem::sellProduct(){
    clearScreen();
    int id, quantity;
    cout << "Enter product ID: ";
    cin >> id;
    cout << "Enter quantity to sell: ";
    cin >> quantity;
    inventory.sellProduct(id, quantity);
}

void InventorySystem::showReport(){
    clearScreen();
    int choice;
    cout << "Select report type: 1) Sales  2) Stock  3) Inventory: ";
    cin >> choice;
    
    vector<Transaction> transactions;
    string line;
    ifstream file("transactions.txt");
    while(getline(file, line)){
        // Parse transaction from line and add to transactions
        // Simplified for now
    }
    file.close();
    
    switch(choice){
        case 1:
            reportGenerator.SalesReport(transactions);
            break;
        case 2:
            reportGenerator.StockReport(inventory.getAllProducts());
            break;
        case 3:
            reportGenerator.InventoryReport(inventory.getAllProducts());
            break;
        default:
            cout << "Invalid choice!" << endl;
    }
}

void InventorySystem::loadData(){
    fileManager.loadProducts(inventory.getAllProducts());
}

void InventorySystem::saveData(){
    fileManager.saveProducts(inventory.getAllProducts());
}

int main(){
    InventorySystem system;
    system.run();
    return 0;
}