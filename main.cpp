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

template <typename T, typename U>
class fillMultimap
{

	public :
		fillMultimap(const T key, const U value, std::multimap<T, U> & mp) : _date(key), _exchange_rate(value), _mp(mp)
		{};

		void operator()(std::multimap<T, U> mp)
		{
			this->_mp.insert(std::make_pair(this->_date, this->_exchange_rate));
		}

		
	private :
		const T _date;
		const U _exchange_rate;
		std::multimap<T, U> & _mp;


};

int main()
{
	std::ifstream csv_file("data.csv");
	std::istream_iterator<std::string> it(csv_file);
	std::istream_iterator<std::string> end;

	while (it!=end)
	{

		std::string data;

		data = *it;

		int ind_coma = (*it).find(',');

		std::string date = data.substr(0, ind_coma);
		std::string exchange_rate = data.substr(ind_coma +1 , (*it).size());

		std::cout << date << " => " << exchange_rate << std::endl;

		/* Here is some parsing */

		++it;
	}

	std::multimap<std::string, std::string> data_map;

	//generate(it, end, fillMultimap());

	return 0;
}