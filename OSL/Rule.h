/*
This is an assessment for OSL Graduate Trainee Program completed by Soujanyo Ray Chaudhuri
10/3/2020
Rule.h
Description - Defines the various rule structures and the Rules structure
*/

#pragma once
#include "Item.h"
#include <vector>

//The discount rule is used when you wish to discount the price of a certain number of items when 
//multiple items are bought
struct discountRule {
	Item i;				//The item this rule applies to
	int thresh;			//threshold number of this item to purchase to avail
	int discounted;		//number of items to discount
	discountRule(Item _i, int t, int d);		
	double compute(map<string, int> skuCtrs);		//computes the value to be discounted
};

//The free rule is used when you wish to offer one item for free when another item is purchased
struct freeRule {
	//The items this rule applies to
	Item paidItem;									
	Item freeItem;
	freeRule(Item p, Item f);
	double compute(map<string, int> skuCtrs);		//computes the value to be given for free
};

struct bulkRule {
	Item i;											//The item this rule applies to
	double newPrice;								//new price after bulk
	int thresh;										//threshold number of this item to purchase to avail
	bulkRule(Item _i, int t, double p);
	double compute(map<string, int> skuCtrs);		//computes the reduced values of goods
};

//This structure holds vectors of all the other rules
struct Rules {
	vector<discountRule> r1;						//All the discount rules to apply
	vector<freeRule> r2;							//All the free rules to apply
	vector<bulkRule> r3;							//All the bulk rules to apply
	Rules();
	Rules(vector<discountRule> _r1, vector<freeRule> _r2, vector<bulkRule> _r3);
	double compute(map<string,int> skuCtrs);										//apply every rule one by one
};