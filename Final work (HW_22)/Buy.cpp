#include "Buy.h"
#include "Product.h"

ostream& operator << (ostream& os, Buy& b)
{
	 os << b.name_product << " " << b.price << " " << b.weight <<
    " " << b.count_order << " " << b.sum_price << " " << b.sum_weight << endl;
	return os;
}

istream& operator>>(istream& is, Buy& b)
{
	is >> b.name_product >> b.price >> b.weight >>
		b.count_order >> b.sum_price >> b.sum_weight;
	return is;
}

void Write_Order_to_file_from_vector(ofstream& file, vector<Buy>& buy)
{
	try
	{
		if (!file.is_open())
		{
			throw runtime_error("The specified file could not be opened\n");
		}
		else
		{
			for (Buy& tmp : buy)
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

void Buy::Set_count_order(int _count_order)
{
	count_order = _count_order;
}

void Buy::Calculate_sum_price_weight()
{
	sum_price = 0; sum_weight = 0;
	sum_price = price * count_order;
	sum_weight = weight * count_order;
}

void Buy::Print_order()
{
	
	cout << left << setw(15) << name_product << left << setw(20) <<
		Convert_price(price) << left << setw(16) << Convert_weight(weight) <<
		left << setw(10) << count_order << left << setw(20) << Convert_price(sum_price) <<
		left << setw(10) << Convert_weight(sum_weight) <<
	    "\n======================================================" <<
		"========================================\n";
}


