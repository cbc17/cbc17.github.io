#include "Item.h"
#include <iostream>
using namespace std;

Item::Item(string n, double p, string ft)
{
    this->name = n;
    this->price = p;
    this->foodType = ft;
    this->finalPrice = 0.0;
}

//return delivery charge amount
double Item::getDelivery()
{
    return delivery;
}

//return tip amount
double Item::getTip()
{
    return tip;
}

//return item price
double Item::getPrice()
{
    return price;
}

double Item::getFinalPrice()
{
    return finalPrice;
}

//return item name
string Item::getName()
{
    return name;
}

string Item::getFoodType()
{
    return foodType;
}

//sets delivery charge
void Item::setDelivery(double d)
{
    delivery = d;
}

//sets tip amount
void Item::setTip(double t)
{
    tip = t;
}

//sets item name
void Item::setName(string n)
{
    name = n;
}

void Item::setFoodType(string ft)
{
    foodType = ft;
}

//sets item price
void Item::setPrice(double p)
{
    price = p;
}

void Item::setFinalPrice(double fp)
{
    finalPrice = fp;
}

//********************************************************
//FreshProduce Child Object
//********************************************************

//creates a produce item. These are items use weight to determine the final price of the item
FreshProduce::FreshProduce(string n, double p) : Item(n, p, "fp")
{
    setPounds(0);
}

//calculate the total price of the item based on the product of the per pound cost times the number of pounds
void FreshProduce::calcPrice()
{
    double finalPrice;
    
    finalPrice = pounds * Item::getPrice();
    
    
    this->setFinalPrice(finalPrice);
}

//returns the weight in pounds
int FreshProduce::getPounds()
{
    return pounds;
}

//sets the weight in whole pounds
void FreshProduce::setPounds(double lbs)
{
    if (pounds > 0) {
        pounds = pounds + lbs;
    }
    else {
        pounds = lbs;
    }
    
}

//********************************************************
//MeasuredProduct Child Object
//********************************************************

//creates a produce item. These are items that require a specific amount to determine the final price of the item
MeasuredProduct::MeasuredProduct(string n, double p) : Item(n, p, "mp")
{
    setQuantity(0);
}

//calculates the price of the item using the price entered when instantiated and the amount entered when instantiated.
void MeasuredProduct::calcPrice()
{
    double finalPrice;
    finalPrice = quantity * Item::getPrice();
    

    this->setFinalPrice(finalPrice);
}

//returns the number of items
int MeasuredProduct::getQuantity()
{
    return quantity;
}

//sets the number of items to be purchased
void MeasuredProduct::setQuantity(int quant)
{
    if (quantity > 0) {
        quantity = quantity + quant;
    }
    else {
        quantity = quant;
    }
}

