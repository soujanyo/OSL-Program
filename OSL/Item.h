/*
This is an assessment for OSL Graduate Trainee Program completed by Soujanyo Ray Chaudhuri
10/3/2020
Item.h
Description - Defines the Item class
*/
#pragma once
#include <string>

using namespace std;
class Item {
private:
	string name;
	string sku;
	double price;
public:
	Item();
	Item(string _name, string _sku, double _price);
	double getPrice();
	string getName();
	string getSKU();
};