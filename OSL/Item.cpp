/*
This is an assessment for OSL Graduate Trainee Program completed by Soujanyo Ray Chaudhuri
10/3/2020
Item.cpp
Description - Implements the Item class and its methods
*/

#include "Item.h"

//default constructor
Item::Item()
{
	name = "default";
	sku = "DEF";
	price = 0.0;
}
//Parameterized constructor 
Item::Item(string _name, string _sku, double _price)
{
	name = _name;
	sku = _sku;
	price = _price;
}

//standard getters
double Item::getPrice()
{
	return price;
}
string Item::getName()
{
	return name;
}
string Item::getSKU()
{
	return sku;
}