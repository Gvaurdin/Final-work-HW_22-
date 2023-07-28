#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip> 
#include "Product.h"

using namespace std;

class Buy : public Product
{
protected:
	int count_order;
	float sum_price, sum_weight;
public:
	Buy() { count_order = 0; sum_price = 0, sum_weight = 0; }
	Buy(const string& _name, double _price, double _weight, int _count_order) :
		Product(_name, _price, _weight), count_order(_count_order)
	{
		sum_price = _price * _count_order;
		sum_weight = _weight * _count_order;
	}
	friend ostream& operator << (ostream& os, Buy& b);
	friend istream& operator >> (istream& is, Buy& b);
	void Set_count_order(int _count);
	double Get_Sum_Price() { return sum_price; }
	double Get_Sum_Weight() { return sum_weight; }
	int Get_count_order() { return count_order; }
	void Calculate_sum_price_weight();
	void Print_order();
	friend void Write_Order_to_file_from_vector(ofstream& file, vector <Buy>& buy);
};

