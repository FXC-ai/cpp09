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
		fillMultimap(std::multimap<std::string, std::string> & mp) : _mp(mp){};

		void operator()(const std::string & data)
		{
			int ind_coma = data.find(',');
			std::string date = data.substr(0, ind_coma);
			std::string exchange_rate = data.substr(ind_coma +1 , data.size());
			this->_mp.insert(std::make_pair(date, exchange_rate));
		}

	private :
		std::multimap<std::string, std::string> & _mp;


};

int main()
{
	// std::ifstream csv_file("data.csv");
	// std::istream_iterator<std::string> it(csv_file);
	// std::istream_iterator<std::string> end;

	// std::multimap<std::string, std::string> data_map;
	
	// //for_each(it, end, fillMultimap(data_map));

	// data_map.insert(std::make_pair("poire","priere"));
	// data_map.insert(std::make_pair("poire2","priere2"));
	// std::multimap<std::string,std::string>::iterator it_mp;


	// for (it_mp = data_map.begin(); it_mp!=data_map.end(); ++it_mp)	
	// {
	// 	std::cout << it_mp->first() << " : " << it_mp->second() << std::endl;
	// }


    std::multimap<std::string, std::string> mp;
 

    mp.insert(std::pair<std::string, std::string>("vd", "vd"));
    mp.insert(std::pair<std::string, std::string>("vd", "vd"));
    mp.insert(std::pair<std::string, std::string>("vd", "vd"));
    mp.insert(std::pair<std::string, std::string>("vd", "vd"));
    mp.insert(std::pair<std::string, std::string>("vd", "vd"));
 

    std::multimap<std::string, std::string>::iterator itr;
    std::cout << "\nThe multimap mp is : \n";
    std::cout << "\tKEY\tELEMENT\n";
    for (itr = mp.begin(); itr != mp.end(); ++itr) {
        std::cout << '\t' << itr->first << '\t' << itr->second
             << '\n';
    }
    std::cout << std::endl;


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