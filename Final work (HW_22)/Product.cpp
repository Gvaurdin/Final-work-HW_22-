#include "Product.h"

Product::Product()
{
	name_product = "";
	count = 0;
	price = 0;
	weight = 0;
	prod_date = "";
	exp_date = "";
}

Product::Product(const Product& obj)
{
	name_product = obj.name_product;
	prod_date = obj.prod_date;
	exp_date = obj.exp_date;
	count = obj.count;
	price = obj.price;
	weight = obj.weight;
}

Product::Product(string _name, double _price, double _weight)
{
	name_product = _name;
	price = _price;
	weight = _weight;
	count = 0;
	prod_date = "";
	exp_date = "";

}

Product::Product(string _name, double _price, double _weight,
	string _prod_date, string _exp_date, int _count)
{
	name_product = _name;
	prod_date = _prod_date;
	exp_date = _exp_date;
	count = _count;
	price = _price;
	weight = _weight;
}

string Product::Convert_price(double _price)
{
	int rub{}, kop{};
	rub = (int)_price;
	kop = _price * 100;
	kop %= 100;
	string r = to_string(rub);
	string c = to_string(kop);
	string rc = r + " rub. " + c + " kop. ";
	return rc;
}

string Product::Convert_weight(double _weight)
{
	int kg{}, g{};
	kg = (int)_weight;
	g = _weight * 100;
	g = (g % 100) * 10;
	string s_kg = to_string(kg);
	string s_g = to_string(g);
	if (kg == 0) return s_g + " g.";
	else if (kg != 0 && g != 0) return s_kg + " kg. " + s_g + " g.";
	else return s_kg + " kg.";
}

void Product::Print_Product()
{
	cout << left << setw(15) << name_product <<
		left << setw(25) << Convert_price(price) <<
		left << setw(15) << Convert_weight(weight) <<
		left << setw(20) << prod_date <<
		left << setw(18) << exp_date << count <<
		"\n======================================================" <<
		"==============================================\n";
}

void Product::Set_Product()
{
	cout << "Enter to new product name :"; cin >> name_product;
	cout << "Enter to new product price (rub.kop) :"; cin >> price;
	while (price < 5.00 || price > 2000.00)
	{
		cout << "Error input price\n" <<
			"Try enter price again : ";
		cin >> price;
	}
	cout << "Enter to new product weight(kg.g) :"; cin >> weight;
	while (weight < 0.01 || weight > 10.00)
	{
		cout << "Error input weight\n" <<
			"Try enter weight again : ";
		cin >> weight;
	}
	cout << "Info prodaction date\n";
	prod_date = Set_Date_Prod();
	cout << "Prodaction date succeffull input\n" <<
		"\n=========================================\n";
	cout << "Info expiration date\n";
	exp_date = Set_Date_Exp();
	cout << "Expiration date succeffull input\n" <<
		"\n=========================================\n";
	cout << "Enter to new product count : ";
	cin >> count;
	cout << "Product succeffull create\n";
	Sleep(1000);
}

string Product::Set_Date_Prod()
{
	int day{}, month{}, year{};
	cout << "Enter to year : ";
	cin >> year;
	while (year < 2022 || year > 2023)
	{
		cout << "Error input date - year\n" <<
			"Enter to date - year again :";
		cin >> year;
	}
	cout << "Enter to month : ";
	cin >> month;
	while (month < 1 || month > 12 ||
		year == 2023 && month > 7)
	{
		cout << "Error input date - month\n" <<
			"Enter to date - month again :";
		cin >> month;
	}
	cout << "Enter to day : ";
	cin >> day;
	while (day < 1 || day > 31)
	{
		cout << "Error input date - day\n" <<
			"Enter to date - day again :";
		cin >> day;
	}
	string day_s, month_s;
	if (day < 10) day_s = '0' + to_string(day);
	else day_s = to_string(day);
	if (month < 10) month_s = '0' + to_string(month);
	else month_s = to_string(month);
	return to_string(year) + '-' + month_s + '-' + day_s;
}

string Product::Set_Date_Exp()
{
	int day{}, month{}, year{};
	cout << "Enter to year : ";
	cin >> year;
	while (year < 2023 || year > 2025)
	{
		cout << "Error input date - year\n" <<
			"Enter to date - year again :";
		cin >> year;
	}
	cout << "Enter to month : ";
	cin >> month;
	while (month < 1 || month > 12 ||
		year == 2023 && month < 8)
	{
		cout << "Error input date - month\n" <<
			"Enter to date - month again :";
		cin >> month;
	}
	cout << "Enter to day : ";
	cin >> day;
	while (day < 1 || day > 31)
	{
		cout << "Error input date - day\n" <<
			"Enter to date - day again :";
		cin >> day;
	}
	string day_s, month_s;
	if (day < 10) day_s = '0' + to_string(day);
	else day_s = to_string(day);
	if (month < 10) month_s = '0' + to_string(month);
	else month_s = to_string(month);
	return to_string(year) + '-' + month_s + '-' + day_s;
}

bool Product::Check_Expiration_date()
{
	string cur_date = gettime();
	if (cur_date.compare(this->exp_date) < 0) return true;
	else if (cur_date.compare(this->exp_date) == 0)
	{
		this->exp_date += "(expires) ";
		return true;
	}
	else return false;
}

string gettime(void)
{
	time_t now = time(0);
	struct tm timeinfo;
	localtime_s(&timeinfo, &now);
	const char* format = "%Y-%m-%d";
	char buffer[80];
	strftime(buffer, 80, format, &timeinfo);
	string str_buffer(buffer);
	return str_buffer;
}

ostream& operator << (ostream& os, Product& p)
{
	os << p.name_product << " " << p.price << " " << p.weight <<
		" " << p.prod_date << " " << p.exp_date << " " << p.count << endl;
	return os;
}

istream& operator>>(istream& is, Product& p)
{
	is >> p.name_product >> p.price >> p.weight >>
		p.prod_date >> p.exp_date >> p.count;
	return is;
}

void Write_Product_to_file(string name_file, Product& p)
{
	ofstream file(name_file, ios::app);
	try
	{
		if (!file.is_open())
		{
			throw runtime_error("The specified file could not be opened\n");
		}
		else
		{
			if (p.Check_Expiration_date())
			{
				file << p;
				file.close();
			}
			else
			{
				cout << "The product is overdue\n";
				Sleep(1500);
			}
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Write_Products_from_vector(string name_file, vector<Product>& p)
{
	ofstream file(name_file, ios::out, ios::binary);
	try
	{
		if (!file.is_open())
		{
			throw runtime_error("The specified file could not be opened\n");
		}
		else
		{
			for (Product& tmp : p)
			{
				file << tmp;
			}
			file.close();
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}


vector<Product> List_Products_Shop(vector<Product>& p)
{
	p.push_back(Product("Milk", 84.35, 0.9, "2023-07-20", "2023-08-01", 10));
	p.push_back(Product("Meat", 257.89, 1.0, "2023-07-25", "2023-07-30", 20));
	p.push_back(Product("Lemonade", 110, 1.5, "2023-07-15", "2024-01-15", 40));
	p.push_back(Product("Chocolate", 110, 0.1, "2023-07-21", "2024-07-21", 5));
	p.push_back(Product("Doshirak", 70.50, 0.1, "2023-07-10", "2024-07-10", 10));
	p.push_back(Product("Orange", 120.70, 1.0, "2023-07-01", "2023-07-25", 30));

	return p;
}
