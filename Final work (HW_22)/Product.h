#pragma once
#include <iostream>
#include <Windows.h>
#include <iomanip> 
#include <vector>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

string gettime(void);

class Product
{
protected:
	string name_product, prod_date, exp_date;
	double price, weight;
	int count;
public:
	Product();
	Product(const Product& obj);
	Product(string _name, double _price, double _weight);
	Product(string _name, double _price, double _weight,
		string _prod_date, string _exp_date, int _count );
	~Product() { ; }
	friend ostream& operator << (ostream& os, Product& p);
	string Convert_price(double _price);
	string Convert_weight(double _weght);
	void Print_Product();
	string& Get_name() { return name_product; }
	double Get_price() { return price; }
	double Get_weight() { return weight; }
	int Get_Count() { return count; }
	void Set_Product();
	string Set_Date_Prod();
	string Set_Date_Exp();
	void Set_count(int _count) { this->count = _count; }
	friend vector<Product> List_Products_Shop(vector <Product>& p);
	friend ostream& operator << (ostream& os, const Product& p);
	friend istream& operator >> (istream& is, Product& p);
	friend void Write_Product_to_file(string name_file, Product& p);
	friend void Write_Products_from_vector(string name_file, vector<Product>& p);
	bool Check_Expiration_date();
};

