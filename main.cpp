#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>

class Display
{
	public :
		template <typename T>
		void operator()(T & a)
		{
			std::cout << a << " - ";
		}
};

class fillMultimap
{

	public :
		fillMultimap(std::string data, std::multimap<std::string, std::string> & mp) : _mp(mp)
		{
			int ind_coma = data.find(',');
			this->_date = data.substr(0, ind_coma);
			this->_exchange_rate = data.substr(ind_coma +1 , data.size());
		};

		void operator()()
		{
			this->_mp.insert(std::make_pair(this->_date, this->_exchange_rate));
		}

	private :
		std::string _date;
		std::string _exchange_rate;
		std::multimap<std::string, std::string> & _mp;


};

int main()
{
	std::ifstream csv_file("data.csv");
	std::istream_iterator<std::string> it(csv_file);
	std::istream_iterator<std::string> end;

	std::multimap<std::string, std::string> data_map;
	
	for_each(it, end, fillMultimap(*it, data_map));
	
	// while (it!=end)
	// {

	// 	std::string data;

	// 	data = *it;

	// 	int ind_coma = (*it).find(',');

	// 	std::string date = data.substr(0, ind_coma);
	// 	std::string exchange_rate = data.substr(ind_coma +1 , (*it).size());

	// 	std::cout << date << " => " << exchange_rate << std::endl;

	// 	/* Here is some parsing */

	// 	++it;
	// }



	return 0;
}