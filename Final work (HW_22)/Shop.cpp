#include "Shop.h"
#include "Buy.h"
#include "Check.h"
#include "Product.h"


void Shop::Print_Price_list()
{
	gotoxy(35, 1);
	cout << "=============PRICE LIST================\n";
	cout << left << setw(3) << "ID" << left << setw(20) << "Product" <<
		left << setw(20) << "Price" << left << setw(12) << "Weight" <<
		left << setw(20) << "Production date" <<
		left << setw(20) << "Expiration date" << "Count\n" <<
		"------------------------------------------------------" <<
		"----------------------------------------------\n";
	int count = 1;
	for (Product& p : price_list)
	{
		cout << left << setw(3) << count;
		p.Print_Product();
		count++;
	}
}

void Shop::Print_Price_Element(int index)
{
}

void Shop::Print_Order_list()
{
	gotoxy(25, 0);
	cout << "=============ORDER LIST================\n\n";
	gotoxy(0, 1);
	cout << left << setw(3) << "ID" << left << setw(20) << "Product" <<
		left << setw(15) << "Price" << left << setw(14) << "Weight" <<
		left << setw(13) << "Count" << left << setw(18) << "Total price" << "Total weight" <<
		"\n----------------------------------------------------------" <<
		"------------------------------------\n";
	int count = 1;
	for (Buy& b : buy_order)
	{
		cout << left << setw(3) << count;
		b.Print_order();
		count++;
	}
}

void Shop::Change_Order_list()
{
	int index{};
	cout << "Enter the item number of the product you want to change or delete :";
	cin >> index;
	index--;
	if (index < 0 || index > buy_order.size() - 1)
	{
		cout << "Error.No order with this index was found\n";
		return;
	}
	else
	{
		char action{};
		cout << "Enter 1 if you want to change the number of products in the item  " <<
			", enter 2 if you want to delete the item\n" <<
			"Enter action : ";
		cin >> action;
		while (action != '1' && action != '2')
		{
			cout << "Error input\n" <<
				"Try enter again : ";
			cin >> action;
		}
		if (action == '1')
		{
			short count{};
			cout << "Enter to new count of products for this position : ";
			cin >> count;
			try
			{
				if (count < 0 || count > 5)
				{
					throw invalid_argument("Error input\n");
				}
				else
				{
					buy_order.at(index).Set_count_order(count);
					buy_order.at(index).Calculate_sum_price_weight();
					cout << "The number of products for the selected " <<
						"item has been successfully changed\n";
					Sleep(1000);
				}
			}
			catch (const std::exception& e)
			{
				cout << e.what();
				system("pause");
				system("cls");
			}
		}
		else if (action == '2')
		{
			vector<Buy>::iterator it = buy_order.begin();
			buy_order.erase(it + (index));
			cout << "The selected position has been successfully deleted\n";
			Sleep(1000);
		}
	}
	system("cls");
}

void Shop::Print_Check()
{
	cout << "                         ============ CHECK ===========\n\n";
	cout << left << setw(3) << "ID" << left << setw(18) << "Product" <<
		left << setw(15) << "Price" << left << setw(16) << "Weight" <<
		left << setw(12) << "Count" << left << setw(18) << "Total price" << "Total weight" <<
		"\n----------------------------------------------------------" <<
		"------------------------------------\n";
	int count = 1;
	for (Check& c : check)
	{
		cout << left << setw(3) << count;
		c.Print_check();
		count++;
	}
	Check tmp;
	double total = this->Calculate_total_price(this->Get_Check());
	cout << tmp.Convert_price(total) << endl;
}

void Shop::Read_Products_and_write_to_price(string name_file)
{
	try
	{
		ifstream file(name_file, ios::in, ios::binary);
		if (!file.is_open())
		{
			throw runtime_error("The specified file could not be opened\n");
		}
		else
		{
			Product tmp;
			while (file >> tmp)
			{
				if (tmp.Check_Expiration_date())
				{
					this->SetProduct(tmp);
				}
			}
			file.close();
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Shop::Read_Order_file_and_write_to_buy_order(string name_file)
{
	try
	{
		ifstream file(name_file, ios::in, ios::binary);
		if (!file.is_open())
		{
			throw runtime_error("The specified file could not be opened\n");
		}
		else
		{
			Buy tmp;
			while (file >> tmp)
			{
				this->SetOrder(tmp);
			}
			file.close();
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Shop::Read_Order_file_and_write_to_check_vector(string name_file)
{
	try
	{
		ifstream file(name_file, ios::in, ios::binary);
		if (!file.is_open())
		{
			throw runtime_error("The specified file could not be opened\n");
		}
		else
		{
			Check tmp;
			while (file >> tmp)
			{
				this->Set_Check(tmp);
			}
			file.close();
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

double Shop::Calculate_total_price(vector<Check>& check)
{
	for (Check& c : check)
	{
		c.total_price += c.Get_Sum_Price();
	}
	return Check::total_price;
}

void Shop::Write_Check_to_file_from_vector(string name_file, vector<Check>& check)
{
	ofstream file(name_file, ios::app, ios::binary);
	try
	{
		if (!file.is_open())
		{
			throw runtime_error("The specified file could not be opened\n");
		}
		else
		{
			file << "                         ============ CHECK ===========\n\n";
			file << left << setw(3) << "ID" << left << setw(18) << "Product" <<
				left << setw(15) << "Price" << left << setw(16) << "Weight" <<
				left << setw(12) << "Count" << left << setw(18) << "Total price" << "Total weight" <<
				"\n----------------------------------------------------------" <<
				"------------------------------------\n";
			int count = 1;
			for (Check& c : check)
			{
				file << left << setw(3) << count << c;
				count++;
			}
			Check tmp;
			double total = this->Calculate_total_price(this->Get_Check());
			file << tmp.Convert_price(total) << endl;
			file.close();
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}
}

void Shop::Read_Check_file(string name_file)
{
	try
	{
		ifstream file(name_file, ios::in);
		if (!file.is_open())
		{
			throw runtime_error("The specified file could not be opened\n");
		}
		else
		{
			string l;
			while (!file.eof())
			{
				l = "";
				getline(file, l);
				cout << l << endl;
			}
			file.close();
		}
	}
	catch (const std::exception& e)
	{
		cout << e.what();
	}

}

void gotoxy(short x, short y)
{
	COORD coord = { x, y };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, coord);
}

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}


void func_menu()
{
	int k = 1;
	char en = 0;
	Shop shop;
	//vector<Product> p;
	//List_Products_Shop(p);
	string file_products = "List_Products.txt", file_order = "List_Order.txt",
		file_check = "List_Check.txt", file_prod = "Work_List_Products.txt";
	//Write_Products_from_vector(file_products, p);
	ofstream buy_file(file_order, ios::out);
	buy_file.close();
	ofstream file_ch(file_check, ios::out);
	file_ch.close();
	ofstream file_pr(file_prod, ios::out);
	file_pr.close();
	shop.Read_Products_and_write_to_price(file_products);
	Write_Products_from_vector(file_prod, shop.Get_buy_price());
	shop.Clear_price_list();
	do
	{
		cout << endl;
		if (en == 80)
		{
			k++;
			if (k == 6)
				k = 1;
		}
		if (en == 72)
		{
			k--;
			if (k == 0)
				k = 5;
		}
		if (en == 13)
		{
			if (k == 1)
			{
				system("cls");
				char menu{};
				shop.Read_Products_and_write_to_price(file_prod);
				int count_price{}, index{};
				while (menu != 27)
				{
					system("cls");
					gotoxy(5, 0);
					cout << "Current date : " << gettime();
					shop.Print_Price_list();
					cout << "Press enter  to add the product to the order\n" <<
						"Press escape to close price list\n";
					menu = _getch();
					if (menu != 27 && menu != 13)
					{
						menu = _getch();
					}
					switch (menu)
					{
					case 13:
					{
						try
						{
							cout << "Enter to id the product : ";
							cin >> index;
							index--;
							if (index < 0 || index > shop.Get_buy_price().size() - 1)
							{
								throw invalid_argument("Error input\n");
							}
							cout << "You select product : " << shop.Get_buy_price().at(index).Get_name() << endl;
							if (shop.Get_buy_price().at(index).Get_Count() == 0)
							{
								SetColor(4, 0);
								cout << "This product is over\n";
								Sleep(1100);
								break;
							}
							cout << "Enter to count this product : ";
							cin >> count_price;
							if (count_price < 0 || count_price > 5 ||
								count_price > shop.Get_buy_price().at(index).Get_Count())
							{
								throw invalid_argument("Error input\n");
							}
							else
							{
								bool valueExists = false;
								for (Buy& b : shop.Get_buy_order())
								{
									if (b.Get_name() == shop.Get_buy_price().at(index).Get_name())
									{
										valueExists = true;
										break;
									}
								}
								if (valueExists)
								{
									int tmp_count = shop.Get_buy_order().at(index).Get_count_order();
									tmp_count += count_price;
									shop.Get_buy_order().at(index).Set_count_order(tmp_count);
									int count = shop.Get_buy_price().at(index).Get_Count();
									count -= count_price;
									shop.Get_buy_price().at(index).Set_count(count);
									cout << "Product succefull add\n";
									Sleep(1000);
									system("cls");
								}
								else
								{
									shop.SetOrder(Buy(shop.Get_buy_price().at(index).Get_name(), shop.Get_buy_price().at(index).Get_price(),
										shop.Get_buy_price().at(index).Get_weight(), count_price));
									int tmp_count = shop.Get_buy_price().at(index).Get_Count();
									tmp_count -= count_price;
									shop.Get_buy_price().at(index).Set_count(tmp_count);
									cout << "Product succefull add\n";
									Sleep(1000);
									system("cls");
								}
							}
						}
						catch (const std::exception& e)
						{
							cout << e.what() << endl;
							system("pause");
							system("cls");
						}
					}
					break;
					case 27:
					{
						system("cls");
						Write_Products_from_vector(file_prod, shop.Get_buy_price());
						ofstream buy_file;
						if (buy_file.eof()) buy_file.open(file_order, ios::out, ios::binary);
						else buy_file.open(file_order, ios::app, ios::binary);
						Write_Order_to_file_from_vector(buy_file, shop.Get_buy_order());
						shop.Clear_price_list();
						shop.Clear_buy_order();
						cout << "Close to price list......\n";
					}
					break;
					default:
						system("cls");
						cout << "Error\n";
						Sleep(1100);
						break;
					}
				}
			}
			if (k == 2)
			{
				system("cls");
				char menu{};
				bool flag = true;
				shop.Read_Order_file_and_write_to_buy_order(file_order);
				if (!shop.Get_buy_order().empty())
				{
					while (flag)
					{
						shop.Print_Order_list();
						cout << "Enter 1 to change or delete the purchase position\n" <<
							"Enter 2 to exit from order list\n" <<
							"Enter action : ";
						cin >> menu;
						switch (menu)
						{
						case '1':
						{
							shop.Change_Order_list();
						}
						break;
						case '2':
						{
							system("cls");
							ofstream buy_file(file_order, ios::out, ios::binary);
							Write_Order_to_file_from_vector(buy_file, shop.Get_buy_order());
							shop.Clear_buy_order();
							cout << "Exit from order list\n";
							flag = false;
						}
						break;
						default:
							cout << "Error!\n";
							break;
						}
					}
				}
				else
				{
					cout << "You not add products to order list!\n";
					Sleep(1500);
				}

				system("cls");
			}
			if (k == 3)
			{
				system("cls");
				gotoxy(0, 0);
				shop.Read_Order_file_and_write_to_check_vector(file_order);
				if (!shop.Get_Check().empty())
				{
					Check::total_price = 0;
					shop.Print_Check();
					cout << "Suceffully operation\n";
					shop.Clear_buy_order();
					ofstream file(file_order, ios::out);
					file.close();
					system("pause");
					char menu{};
					system("cls");
					Check::total_price = 0;
					shop.Write_Check_to_file_from_vector(file_check, shop.Get_Check());
					shop.Clear_buy_order();
					shop.Clear_check();
					Check::total_price = 0;
					cout << "Enter 1 to show check history\n" <<
						"Enter 2 to close current session\n" <<
						"Your action : ";
					cin >> menu;
					if (menu != '1' && menu != '2')
					{
						cout << "Error input\n" <<
							"Try input command again : ";
						cin >> menu;
					}
					switch (menu)
					{
					case'1':
					{
						system("cls");
						shop.Read_Check_file(file_check);
						system("pause");
					}
					break;
					case '2':
					{
						system("cls");
						cout << "Close current session...... \n";
						Sleep(1500);
					}
					break;
					}
				}
				else
				{
					cout << "You not add products to order list!\n";
					Sleep(1500);
				}

			}

			if (k == 4)
			{
				system("cls");
				char menu{};
				cout << "Enter 1 if you want to record a new product.\n" <<
					"Enter 2 if you want to top up the product quantity.\n" <<
					"Enter 3 if you want to close the editor\n" <<
					"Enter action :";
				cin >> menu;
				while (menu != '1' && menu != '2' &&
					menu != '3')
				{
					cout << "Error input\n" <<
						"Enter action again :";
					cin >> menu;
				}
				switch (menu)
				{
				case '1':
				{
					system("cls");
					Product tmp;
					tmp.Set_Product();
					Write_Product_to_file(file_prod, tmp);
					cout << "Your new product to record !\n";
					Sleep(1500);
				}
				break;
				case '2':
				{
					system("cls");
					int index{}, count_price{};
					shop.Read_Products_and_write_to_price(file_prod);
					shop.Print_Price_list();
					try
					{
						cout << "Enter to id the product : ";
						cin >> index;
						index--;
						if (index < 0 || index > shop.Get_buy_price().size() - 1)
						{
							throw invalid_argument("Error input\n");
						}
						else
						{
							cout << "You select product : " << shop.Get_buy_price().at(index).Get_name() << endl;
							cout << "Enter to count this product : ";
							cin >> count_price;
							if (count_price < 0 || count_price > 50)
							{
								throw invalid_argument("Error input\n");
							}
							shop.Get_buy_price().at(index).Set_count(count_price);
							Write_Products_from_vector(file_prod, shop.Get_buy_price());
							shop.Clear_price_list();
							cout << "Product succefull add\n";
							Sleep(1000);

						}
					}
					catch (const std::exception& e)
					{
						cout << e.what() << endl;
						system("pause");
						system("cls");
					}

				}
				break;
				case '3':
				{
					system("cls");
					cout << "Close editor...... \n";
					Sleep(1500);
				}
				break;
				}
			}

			if (k == 5)
			{
				cout << "Exit from programm....\n";
				Sleep(1000);
				break;
			}

		}
		system("cls");
		gotoxy(28, 0);
		SetColor(11);
		cout << "Shop Magnit\n";
		SetColor(7);
		if (k == 1)
			SetColor(13);
		gotoxy(15, 2);
		cout << "1. Show the list of products and add the selected products to the order" << endl;
		SetColor(7);

		if (k == 2)
			SetColor(13);
		gotoxy(15, 3);
		cout << "2. Show an order with selected products " << endl;
		SetColor(7);
		if (k == 3)
			SetColor(13);
		gotoxy(15, 4);
		cout << "3. Place an order and make a purchase " << endl;
		SetColor(7);
		if (k == 4)
			SetColor(13);
		gotoxy(15, 5);
		cout << "4. Set count product or add new product to file " << endl;
		SetColor(7);
		if (k == 5)
			SetColor(13);
		gotoxy(15, 6);
		cout << "5. Exit the shop " << endl;
		SetColor(7);
	} while (en = _getch());
}
