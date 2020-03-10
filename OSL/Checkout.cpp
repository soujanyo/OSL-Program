/*
This is an assessment for OSL Graduate Trainee Program completed by Soujanyo Ray Chaudhuri
10/3/2020
Checkout.cpp
Description - Implements the functions of the Checkout class and the rule structures
*/

#include "Checkout.h"
#include "Rule.h"

//Default constructor 
Checkout::Checkout()
{
}
//Parameterized constructor
Checkout::Checkout(Rules _rules, vector<Item> _items)
{
	rules = _rules;
	items = _items;
}

//Calculates the user's total by computing the total were it not for any rules
//Then computing the amount from the total bill to subtract in different discounts
//Returns the net bill to the user
double Checkout::total()
{
	double netBill = 0;
	for (map<string, int >::const_iterator it = skuCtrs.begin();
		it != skuCtrs.end(); ++it)
	{
		double price;
		for (int i = 0; i < items.size(); i++)
		{
			if (items[i].getSKU() == it->first)
			{
				price = items[i].getPrice();
			}
		}
		netBill += price * it->second;
	}
	netBill -= rules.compute(skuCtrs);
	return netBill;
}

//Scan an item and increment the map counter
void Checkout::scan(int item)
{
	string s = getSKUByID(item);
	if (skuCtrs[s] == 0)
		skuCtrs[s] = 1;
	else
		skuCtrs[s]++;
}

//helper function to scan items by ID
string Checkout::getSKUByID(int i) {
	switch (i)
	{
	case 1:	return "ipd";	break;
	case 2:	return "mbp";	break;
	case 3:	return "atv";	break;
	case 4:	return "vga";	break;
	default:	return "invalid";
	}
}

//discount rule constructor
discountRule::discountRule(Item _i, int t, int d)
{
	i = _i;
	thresh = t;
	discounted = d;
}
//compute value to discount
double discountRule::compute(map<string, int> skuCtrs)
{
	//if the number scanned exceeds the threshold to apply the discount
	if (skuCtrs[i.getSKU()] >= thresh)
	{
		int retVal = skuCtrs[i.getSKU()] / thresh;
		return retVal * (discounted*i.getPrice());		
	}
	return 0.0; 	//no amount to be reduced
}

//free rule constructor
freeRule::freeRule(Item p, Item f)
{
	paidItem = p;
	freeItem = f;
}

double freeRule::compute(map<string, int> skuCtrs)
{
	//For every paid item purchased, discount the value of one free item in the cart
	//We look for the minimum between paid item number and free item number so we don't accidentally give an extra free item
	int numFree = (skuCtrs[paidItem.getSKU()] > skuCtrs[freeItem.getSKU()]) ? skuCtrs[freeItem.getSKU()] : skuCtrs[paidItem.getSKU()];
	return numFree * freeItem.getPrice();
}

//bulk rule constructor
bulkRule::bulkRule(Item _i, int t, double p)
{
	i = _i;
	thresh = t;
	newPrice = p;
}
double bulkRule::compute(map<string, int> skuCtrs)
{
	//if the number scanned exceeds the threshold to apply the bulk rule
	if (skuCtrs[i.getSKU()] > thresh)
	{
		//difference between original amount * number of items and special price * number of items
		return (skuCtrs[i.getSKU()] * i.getPrice() - skuCtrs[i.getSKU()] * newPrice);	
	}
	return 0.0;	//no amount to be reduced
}

//Rules constructors
Rules::Rules()
{

}
Rules::Rules(vector<discountRule> _r1, vector<freeRule> _r2, vector<bulkRule> _r3)
{
	r1 = _r1;
	r2 = _r2;
	r3 = _r3;
}
//Iterate through each of the rule vectors and compute the amount to discount for each of them 
double Rules::compute(map<string,int> skuCtrs)
{
	double toSub = 0;						//amount to subtract from total 
	for (int i = 0; i < r1.size(); i++)
	{
		toSub += r1[i].compute(skuCtrs);
	}
	for (int i = 0; i < r2.size(); i++)
	{
		toSub += r2[i].compute(skuCtrs);
	}
	for (int i = 0; i < r3.size(); i++)
	{
		toSub += r3[i].compute(skuCtrs);
	}
	return toSub;
}