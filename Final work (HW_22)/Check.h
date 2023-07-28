#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <conio.h>
#include <iomanip> 
#include "Buy.h"

using namespace std;

class Check : public Buy
{
public:
	static double total_price;
	Check() { ; }
	Check(const string& _name, double _price, double _weight, int _count) :
		Buy(_name, _price, _weight,count) {}
	friend ostream& operator << (ostream& os, Check& c);
	void Print_check();
	void Print_check_from_file();
	friend istream& operator >> (istream& is, Check& c);
};

