#pragma once
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <iomanip> 
#include <string>
#include <vector>
#include "Buy.h"
#include "Check.h"
#include "Product.h"

using namespace std;

void gotoxy(short x, short y);
enum ConsoleColor
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue,
	LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};
void SetColor(int text, int background = Black);

void func_menu();

class Shop
{
	vector <Product> price_list;
	vector <Buy> buy_order;
	vector <Check> check;
public:
	Shop() { ; }
	void SetProduct(const Product& product) { price_list.push_back(product); }
	void Print_Price_list();
	void Print_Price_Element(int index);
	void SetOrder(const Buy& order) { buy_order.push_back(order); }
	void Print_Order_list();
	void Change_Order_list();
	void Set_Check(const Check& _check) { check.push_back(_check); }
	void Print_Check();
	vector <Buy>& Get_buy_order() { return buy_order; }
	void Clear_buy_order() { buy_order.clear(); }
	void Clear_check() { check.clear(); }
	void Read_Products_and_write_to_price(string name_file);
	void Read_Order_file_and_write_to_buy_order(string name_file);
	void Read_Order_file_and_write_to_check_vector(string name_file);
	vector <Product>& Get_buy_price() { return price_list; }
	vector <Check>& Get_Check() { return check; }
	double Calculate_total_price(vector <Check>& check);
	void Clear_price_list() { price_list.clear(); }
	void Write_Check_to_file_from_vector(string name_file, vector <Check>& check);
	void Read_Check_file(string name_file);
};

