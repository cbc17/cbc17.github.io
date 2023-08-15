#ifndef ITEM_H
#define ITEM_H

#include <string>
using namespace std;

class Item
{
private:
	static double delivery;
	static double tip;
	string name;
	string foodType;
	double price;
	double finalPrice;

public:
	Item(string, double, string);
	static double getDelivery();
	static double getTip();
	double getPrice();
	double getFinalPrice();
	string getName();
	string getFoodType();

	static void setDelivery(double);
	static void setTip(double);
	void setName(string);
	void setFoodType(string);
	void setPrice(double);
	void setFinalPrice(double);
};

class FreshProduce : public Item {
private:
	double pounds;
public:
	FreshProduce(string, double);
	void calcPrice();
	int getPounds();
	void setPounds(double);

};

class MeasuredProduct : public Item {
private:
	int quantity;
public:
	MeasuredProduct(string, double);
	void calcPrice();
	int getQuantity();
	void setQuantity(int);
};
#endif // !ITEM_H

