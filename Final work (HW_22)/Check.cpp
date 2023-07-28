#include "Check.h"
#include "Buy.h"

ostream& operator<<(ostream& os, Check& c)
{
	//os << c.name_product << " " << c.price << " " << c.weight << " " <<
	//	c.count_order << " " << c.sum_price << " " << c.sum_weight <<
	//	" " << c.Convert_price(Check::total_price) << endl;
	os << left << setw(15) << c.name_product << left << setw(20) <<
		c.Convert_price(c.price) << left << setw(16) << c.Convert_weight(c.weight) <<
		left << setw(10) << c.count_order << left << setw(20) << c.Convert_price(c.sum_price) <<
		left << setw(10) << c.Convert_weight(c.sum_weight) <<
		endl << "======================================================" <<
		"========================================" << endl;
	return os;
}

istream& operator>>(istream& is, Check& c)
{
	is >> c.name_product >> c.price >> c.weight >> c.count_order >>
		c.sum_price >> c.sum_weight;
	return is;
}

void Check::Print_check()
{
	Print_order();
}

void Check::Print_check_from_file()
{
	Print_order();
	cout << Check::total_price << endl;
}

double Check::total_price = 0.0;
