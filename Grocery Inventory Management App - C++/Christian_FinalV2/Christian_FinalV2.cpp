#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include "Item.h"

using namespace std;

//creating my vector to serve as my cart
vector <FreshProduce*> produceCart;
vector <MeasuredProduct*> frozenCart;
vector <Item*> totalInventory;
vector <MeasuredProduct*> frozen;
vector <FreshProduce*> produce;
vector <FreshProduce*> meats;

//initializing my static variables
double Item::delivery = 0.0;
double Item::tip = 0.0;

//prototypes
int introMenu();
void printCustomerMenu();
void printEmployeeMenu();
void printInventory();
void printFoods(vector<MeasuredProduct*> inventory);
void printFoods(vector<FreshProduce*> inventory);
void addItem();
void addItem(string name_, double price_, string foodType_);
void sortFoodLists();
void printCart();
void editItem();
void printReceipt();
void loadFoodInventoryFile();
void removeItem();


//constant values for the delivery and tip rates
const double DELIVERY = 20.00;

//several arrays used in printing out menues
string mainMenu[] = { "(1) Fresh Produce", "(2) Meat and Seafood", "(3) Frozen Foods", "(4) Display Cart", "(5) Checkout"};
string employeeMenu[] = { "(1) Add item", "(2) Edit Item", "(3) Delete Item", "(4) Display Inventory", "(5) Edit Discounts", "(6) Exit" };

//keeps track of the total amount of different items in the car
//total is the to cost at the end
int cartAmount = 0;
double total = 0;

int main()
{
    
    
    loadFoodInventoryFile();//this method loads a text file to fill out the initial inventory
    
    int selection;
    cout << "Welcome to Shopper's Grocery Store" << endl;
    cout << "Please choose if you wish to sign in as an administrator or shopper:" << endl;
    cout << "(1) Administrator" << endl; //this option lets us edit and adjust prices, items, names, remove items from inventory, 
    //andeventually would allow us to apply discounts
    cout << "(2) Shopper" << endl;
    //This option is the customer shopping experience
    cin >> selection;
    
    switch (selection) {
    case 1:

        printEmployeeMenu();
        cin >> selection;
        while (selection > 6 || selection < 1) {
            cout << "Please input a single digit choice from 1-6" << endl;
            cin >> selection;
        }
        while (selection != 6) {
            switch (selection) {
            case 1:
                addItem();//Manually add a new item by inputing name, price per pound or unit, and the food type for it to be sorted.
                break;
            case 2:
                editItem(); //Edit the attributes of any item on the inventory list
                break;
            case 3:
                removeItem();//Remove an item from inventory
                break;
            case 4:
                
                printInventory();//Prints the most current version of the inventory list
                cin.get();
                break;
            case 5:
                //Discounts Coming Soon
                /*I see discounts working easily. I would add another field to the item class that would be an int called discount. Initially set to zero,
                the admin would be able to create a discount associated with a number and would change the discount field of an item to match said number, thus
                applying the discount to it. You also would be able to sort by foodType to apply blanket discounts to the different sections like produce
                or frozen foods.*/

                break;
            }
            printEmployeeMenu();
            cin >> selection;
            system("CLS");
        }
        cout << "Welcome to Shopper's Grocery Store" << endl;
        cout << "Please choose if you wish to sign in as an administrator or shopper:" << endl;
        cout << "(1) Administrator" << endl;
        cout << "(2) Shopper" << endl;
        cin >> selection;

    case 2:
        //This is the shoppers side. We clear all vectors except the main inventory so each one is re-sorted and up to date with the 
        //latest inventory list updates from the admin side.
        frozen.clear();
        meats.clear();
        produce.clear();
        frozenCart.clear();
        produceCart.clear();
        sortFoodLists(); //this method sorts through the inventory list and adds items to the different food type vectors based on the foodType attribute

        

        if (introMenu() == 0) {
            return 0;
        }
        printCustomerMenu();
        cin >> selection;
        while (selection > 5 || selection < 1) {
            cout << "Please input a single digit choice from 1-5" << endl;
            cin >> selection;
        }
        system("CLS");
        while (selection != 5)
        {
            switch (selection)
            {
            case 1:
                //Produce
                printFoods(produce);
                cout << "Choose an item to add to the cart:\n" << endl;
                cin >> selection;
                while (selection > produce.size()) {
                    cout << "Item does not exist, please enter another choice:" << endl;
                    cin >> selection;
                }
                selection = selection - 1;
                while (selection != -1) {
                    /*This section has been streamlined from the midterm. Now instead of having to hard code each item and have each one have its own 
                    switch choice, the specified food list is displayed and then input is processed based on what the list says there.*/
                    cout << "Enter how many pounds of the selected item you want:\n" << endl;
                    double p;
                    cin >> p;
                    produce[selection]->setPounds(p);
                    produce[selection]->calcPrice();
                    produceCart.push_back(produce[selection]);
                    cartAmount++;
                    system("CLS");
                    printFoods(produce);
                    cout << "Choose an item to add to the cart:\n" << endl;
                    cin >> selection;
                    selection = selection - 1;
                }
                
                break;
            case 2:
                //Meats
                printFoods(meats);
                cout << "Choose an item to add to the cart:\n" << endl;
                cin >> selection;
                selection = selection - 1;
                while (selection != -1) {
                    cout << "Enter how many pounds of the selected item you want:\n" << endl;
                    double p;
                    cin >> p;
                    meats[selection]->setPounds(p);
                    meats[selection]->calcPrice();
                    produceCart.push_back(meats[selection]);
                    cartAmount++;
                    system("CLS");
                    printFoods(meats);
                    cout << "Choose an item to add to the cart:\n" << endl;
                    cin >> selection;
                    selection = selection - 1;
                }
                
                break;
            case 3:
                //Frozen
                printFoods(frozen);
                cout << "Choose an item to add to the cart:\n" << endl;
                cin >> selection;
                selection = selection - 1;
                while (selection != -1) {

                    cout << "Enter how many of the selected item you want:\n" << endl;
                    double q;
                    cin >> q;
                    frozen[selection]->setQuantity(q);
                    frozen[selection]->calcPrice();
                    frozenCart.push_back(frozen[selection]);
                    cartAmount++;
                    system("CLS");
                    printFoods(frozen);
                    cout << "Choose an item to add to the cart:\n" << endl;
                    cin >> selection;
                    selection = selection - 1;
                }
                
                break;
            case 4:
                //Displaying Cart Contents
                printCart();
                cin.get();
                break;
            }

            cin.get();
            printCustomerMenu();
            cin >> selection;
            system("CLS");

        }
        //When option five is show we check out
        printReceipt();

        return 0;
    }
}

//method used when loading the initial text file for inventory
void addItem() {
    string name;
    string foodType;
    double price;

    cout << "Enter the name of the item:\n";
    cin >> name;
    cout << "Enter the price of the item:\n";
    cin >> price;
    cout << "Enter the type of item (Frozen, Produce, or Meat):\n";
    cin >> foodType;


    Item* i = new Item(name, price, foodType);

    totalInventory.push_back(i);

}

//different version of the method used when manually adding new items
void addItem(string name_, double price_, string foodType_) {
    string name = name_;
    double price = price_;
    string foodType = foodType_;
    

    Item* i = new Item(name, price, foodType);

    totalInventory.push_back(i);

}

//method to edit any item on the list. 
void editItem() {
    printInventory();

    cout << "Select item to edit:\n" << endl;
    int item;
    cin >> item;
    item = item - 1;
    cout << "Do you want to edit:\n" << endl;
    cout << "(1) Item Name" << endl;
    cout << "(2) Item Price" << endl;
    cout << "(3) Item Type" << endl;
    int attribute;
    cin >> attribute;
    if (attribute == 1) {
        cout << "Enter new item name:\n" << endl;
        string newName;
        cin >> newName;
        totalInventory[item]->setName(newName);
    }
    else if (attribute == 2) {
        cout << "Enter new price:\n" << endl;
        double newPrice;
        cin >> newPrice;
        totalInventory[item]->setPrice(newPrice);
    }
    else if (attribute == 3) {
        cout << "Enter new item type (Produce, Meat, or Frozen):\n" << endl;
        string newType;
        cin >> newType;
        totalInventory[item]->setFoodType(newType);
    }
    sortFoodLists();
}

void removeItem() {
    printInventory();
    cout << "Select Item to delete:" << endl;
    int item;
    cin >> item;
    item = item - 1;
    totalInventory.erase(totalInventory.begin() + item);
    sortFoodLists();
}

//loads the inventory file and creates the inventory list of different items
void loadFoodInventoryFile() {
    fstream inFile;
    string n;
    string ft;
    double p;

    inFile.open("inventory.txt", ios::in);
    if (inFile.is_open()) {
        string line;
        while (!inFile.eof()) {
            getline(inFile, n);
            getline(inFile, line);
            p = stod(line);
            getline(inFile, ft);
            addItem(n, p, ft);
        }
    }
    inFile.close();
    sortFoodLists();
}

//This method sorts of the different sections (Produce, Meats, Frozen) based on the food type attribute each item has
void sortFoodLists() {
    frozen.clear();
    meats.clear();
    produce.clear();

    string name;
    double price;

    for (int i = 0; i < totalInventory.size(); i++) {

        name = totalInventory[i]->getName();
        price = totalInventory[i]->getPrice();

        if (totalInventory[i]->getFoodType() == "Frozen") {
            MeasuredProduct* f = new MeasuredProduct(name, price);
            frozen.push_back(f);
        }
        else if (totalInventory[i]->getFoodType() == "Produce") {
            FreshProduce* p = new FreshProduce(name, price);
            produce.push_back(p);
        }
        else if (totalInventory[i]->getFoodType() == "Meat") {
            FreshProduce* m = new FreshProduce(name, price);
            meats.push_back(m);
        }
    }
}

//these methods takes a vector of food items and prints them
//when their menues are selected
void printInventory() {
    /*cin.get();*/
    cout << "*******************************************************************" << endl;
    cout << "\t\tTotal Inventory\n\n\n" << endl;
    for (int i = 0; i < totalInventory.size(); i++) {
        cout << setw(5) << i + 1 << ". " << setw(15) << totalInventory[i]->getName() << setw(10) << fixed << setprecision(2) << "\t$" << totalInventory[i]->getPrice() << endl;
    }
    cout << "\n\nPress any key to Exit" << endl;
    
    cout << "*******************************************************************" << endl;
    /*cin.get();
    system("CLS");*/
}

void printFoods(const vector<FreshProduce*> inventory) {
    cout << "*******************************************************************" << endl;
    for (int i = 0; i < inventory.size(); i++) {
        cout << setw(5) << i + 1 << ". " << setw(15) << inventory[i]->getName() << setw(10) << "$" << inventory[i]->getPrice() << " / pound" << endl;
    }
    cout << "\n\n(0) Exit" << endl;
    cout << "*******************************************************************" << endl;
}

void printFoods(const vector<MeasuredProduct*> inventory) {
    cout << "*******************************************************************" << endl;
    for (int i = 0; i < inventory.size(); i++) {
        cout << setw(5) << i + 1 << ". " << setw(15) << inventory[i]->getName() <<  setw(10) << "$" << inventory[i]->getPrice() << " / unit" << endl;
    }
    cout << "\n\n(0) Exit" << endl;
    cout << "*******************************************************************" << endl;
}

//This menu displays the initial menu where users choose delivery, pickup, or to cancel using the app
int introMenu() {
    cout << "*******************************************************************" << endl;
    cout << "Make A Selection: \n" << endl;
    cout << "(1) Pickup" << endl;
    cout << "(2) Delivery" << endl;
    cout << "\n\n(0) Exit" << endl;
    cout << "*******************************************************************" << endl;
    int selection;
    cin >> selection;
    while (selection < 0 || selection > 2) {
        cout << "Enter 0, 1, or 2:" << endl;
        cin >> selection;
    }
    system("CLS");

    //Static variables are changed if delivery is set
    if (selection == 2) {
        Item::setDelivery(DELIVERY);

    }
    if (selection < 1 || selection == 0) {
        cout << "Good-bye." << endl;
        return 0;
    }
    else { return 1; }
    
}

//this method prints the main menu when called
void printCustomerMenu() {
    cout << "*******************************************************************" << endl;
    
    int size = sizeof(mainMenu)/sizeof(mainMenu[0]);
    for (int i = 0; i < size; i++) {
        cout << mainMenu[i] << endl;
    }
    
    cout << "*******************************************************************" << endl;
}

void printEmployeeMenu() {
    cout << "*******************************************************************" << endl;

    int size = sizeof(employeeMenu) / sizeof(employeeMenu[0]);
    for (int i = 0; i < size; i++) {
        cout << employeeMenu[i] << endl;
    }

    cout << "*******************************************************************" << endl;
}


//This method prints the formatted cart, first come produce and meats, then frozen items
void printCart() {
    total = 0;
    cout << "*******************************************************************" << endl;
    for (int i = 0; i < produceCart.size(); i++) {
        cout << produceCart[i]->getName() << endl;
        cout << setw(5) << produceCart[i]->getPounds() << fixed << setprecision(2) << " lbs at $" << produceCart[i]->getPrice() << fixed << setprecision(2) << "\t$" << produceCart[i]->getFinalPrice() << endl;
        //this loop sorts for matching items on the cart vector, and removes duplicates while the total pounds is still counted together
        for (int j = i+1; j < produceCart.size(); j++) {
            if (produceCart[j]->getName() == produceCart[i]->getName() && produceCart[j]->getFoodType() == produceCart[i]->getFoodType()) {
                produceCart.erase(produceCart.begin() + j);
                cartAmount--;
            }
        }
        //cout << setw(15) << right << produceCart[i]->getPounds() << fixed << setprecision(2) << " lbs at $" << produceCart[i]->getPrice() << endl;
        total += produceCart[i]->getFinalPrice();
    }

    for (int i = 0; i < frozenCart.size(); i++) {
        cout << frozenCart[i]->getName() << endl;
        cout << setw(5) << right << frozenCart[i]->getQuantity() << fixed << setprecision(2) << " ea at $" << frozenCart[i]->getPrice() << fixed << setprecision(2) << "\t$" << frozenCart[i]->getFinalPrice() << endl;

        for (int j = i + 1; j < frozenCart.size(); j++) {
            if (frozenCart[j]->getName() == frozenCart[i]->getName()) {
                frozenCart.erase(frozenCart.begin() + j);
                cartAmount--;
            }
        }


        total += frozenCart[i]->getFinalPrice();
    }
    cout << " " << endl;
    cout << setw(20) << right << "Total Items: " << cartAmount << endl;
    cout << " " << endl;
}

void printReceipt() {
    //Prints out the final checkout
    //Using the cart vector, I pull pointers to each object that was added and print out their names and final price values
    //While doing this, I also total up all the values to serve as the final total
    cout << "Do you want to leave a tip? Please enter tip amount below:\n\n" << endl;
    double t;
    cin >> t;
    Item::setTip(t);

    printCart();
    //Delivery and Tip charges are added if delivery was selected
    cout << setw(20) << right << "Delivery Charge:" << fixed << setprecision(2) << "\t$" << Item::getDelivery() << endl;
    total += Item::getDelivery();
    cout << setw(20) << right << "Tip Charge:" << fixed << setprecision(2) << "\t$" << Item::getTip() << endl;
    total += Item::getTip();
    cout << " " << endl;
    cout << setw(20) << right << "Total:" << fixed << setprecision(2) << "\t$" << total << endl;
    cout << "*******************************************************************" << endl;
}