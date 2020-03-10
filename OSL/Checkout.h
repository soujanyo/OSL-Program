/*
This is an assessment for OSL Graduate Trainee Program completed by Soujanyo Ray Chaudhuri
10/3/2020
Checkout.h
Description - Defines the Checkout class
*/
#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

#include "Rule.h"
#include "Item.h"

using namespace std;

class Checkout {
public:
	map<string, int> skuCtrs;			//map of item sku to number of items purchased
	vector<Item> items;					//vector of items available
	Rules rules;						//rules to apply
	Checkout();
	Checkout(Rules _rules, vector<Item> _items);
	double total();						//calculate user's total
	void scan(int);						//scan an item by id
	string getSKUByID(int);				//helper function to scan items 
};