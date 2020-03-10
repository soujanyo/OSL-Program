/*
This is an assessment for OSL Graduate Trainee Program completed by Soujanyo Ray Chaudhuri
10/3/2020
Main.cpp
Description - Driver code for the program
*/

//importing libraries and header files
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iomanip>

#include "Item.h"
#include "Checkout.h"
#include "Rule.h"

using namespace std;

//helper function to print the items in the items vector. 
//if more items are added when the store expands, no need to re-write
inline void printItem(Item item)
{
	static int i = 1;
	cout << i << ". " << item.getName() << " \t Price = " << item.getPrice() << endl;
	i++;
}

//main function 
int main()
{
	vector<Item> items;											//vector of type Item to store all items the store has


	//inserting the different items and their details
	items.push_back(Item("Super iPad", "ipd", 549.99));			
	items.push_back(Item("MacBook Pro", "mbp", 1399.99));
	items.push_back(Item("Apple TV", "atv", 109.50));
	items.push_back(Item("VGA adapter", "vga", 30.00));

	//prints for user
	cout << "Welcome to Shopping-R-Us!" << endl << endl << endl;
	cout << "List of items available for purchase:" << endl;
	for_each(items.begin(), items.end(), printItem);

	//Defining the different rules
	//Simple create another object of the required rule type to add a new rule 
	discountRule atvDisc(items[2],3,1);
	freeRule vgaFree(items[1], items[3]);
	bulkRule ipadBulk(items[0], 4, 499.99);

	//We use vectors of different rules here so it is easily extendable to multiple rules
	vector<discountRule> r1;
	r1.push_back(atvDisc);
	vector<freeRule> r2;
	r2.push_back(vgaFree);
	vector<bulkRule> r3;
	r3.push_back(ipadBulk);

	//Initializing the Rules object with various vectors of rules
	Rules rules(r1, r2, r3);

	//Creating an object of the Checkout class with our newly defined rules and all the items in the store
	Checkout co(rules,items);


	//For simplified use, instead of accepting strings, the store manage just has to enter number to scan constantly
	//Will run until a special code (-1) is given 
	while (1)
	{
		int temp;
		cout << "What would you like to scan? (Enter any of the above item numbers or -1 to begin checkout)" << endl << endl;
		cin >> temp;				//accept user input
		if (temp == -1)	break;		//break from loop
		else
		{
			co.scan(temp);			//scan item
		}
	}
	//print final total
	cout << "Your total is: $" <<  co.total() << endl;
	system("pause");
	return 0;
}