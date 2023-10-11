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

int main()
{
	std::ifstream csv_file("data.csv");


	std::istream_iterator<std::string> it(csv_file);
	std::istream_iterator<std::string> end;

	std::map<std::string, std::string> data_map;


	while (it!=end)
	{


		// std::stringstream ss(*it);
    	// std::string date;
		// while (!ss.eof())
		// {
		// 	getline(ss, date, ',');
		// 	std::cout << date << std::endl;
		// }

		std::string data;

		data = *it;


		int ind_coma = (*it).find(',');

		std::string date = data.substr(0, ind_coma);
		std::string exchange_rate = data.substr(ind_coma +1 , (*it).size());

		std::cout << date << " => " << exchange_rate << std::endl;
		++it;
	}



	


	return 0;
}