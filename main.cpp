#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>

class Display
{
public:
    template <typename T>
    void operator()(T & a)
    {
        std::cout << a << " - ";
    }
};

class fillMultimap
{
	public:
		fillMultimap(std::multimap<std::string, std::string> & mp) : _mp(mp) {}

		void operator()(const std::string & data)
		{
			int ind_coma = data.find(',');
			std::string date = data.substr(0, ind_coma);
			std::string exchange_rate = data.substr(ind_coma + 1, data.size());
			this->_mp.insert(std::make_pair(date, exchange_rate));
		}

	private:
		std::multimap<std::string, std::string> & _mp;
};

int main()
{
    std::ifstream csv_file("data.csv");
    std::istream_iterator<std::string> it(csv_file);
    std::istream_iterator<std::string> end;

    std::multimap<std::string, std::string> data_map;
    
	++it;

    std::for_each(it, end, fillMultimap(data_map));

    std::multimap<std::string, std::string>::iterator itr;

	int h = 0;
    for (itr = data_map.begin(); itr != data_map.end(); ++itr)
	{
        std::cout << itr->first << " => " << itr->second << std::endl;
		h++;
    }

	std::cout << h << std::endl;




    return 0;
}
