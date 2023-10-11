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
		fillMultimap(std::multimap<std::string, float> & mp) : _mp(mp) {}

		void operator()(const std::string & data)
		{
			int ind_coma = data.find(',');
			std::string date = data.substr(0, ind_coma);
			std::string exchange_rate_str = data.substr(ind_coma + 1, data.size());
			float exchange_rate = atof(exchange_rate_str.c_str());
			this->_mp.insert(std::make_pair(date, exchange_rate));
		}

	private:
		std::multimap<std::string, float> & _mp;
};

class MultimapInput
{
	public:
		MultimapInput(const std::string fileName);
		std::multimap<std::string, float> get_mp_input();

	private:
		const std::string _fileName;
		std::multimap<std::string, float> _mp_input;
};

MultimapInput::MultimapInput(const std::string fileName) : _fileName(fileName)
{
	std::ifstream input_file(this->_fileName);

	std::string temp;
	std::getline(input_file, temp);
	while (std::getline(input_file, temp))
	{
		int indexVL = temp.find(" | ");
		std::string date = temp.substr(0, indexVL);
		float value = atof((temp.substr(indexVL + 3, temp.size())).c_str());
		//std::cout << date << " " << value << std::endl;
		this->_mp_input.insert(std::make_pair(date, value));


	}

};

std::multimap<std::string, float> MultimapInput::get_mp_input()
{
	return this->_mp_input;
};

int main()
{
    // std::ifstream csv_file("data.csv");
    // std::istream_iterator<std::string> it(csv_file);
    // std::istream_iterator<std::string> end;

    // std::multimap<std::string, float> data_map;
    
	// ++it;

    // std::for_each(it, end, fillMultimap(data_map));

    // std::multimap<std::string, float>::iterator itr;

    // for (itr = data_map.begin(); itr != data_map.end(); ++itr)
	// {
    //     std::cout << itr->first << " => " << itr->second << std::endl;
    // }

	// std::ifstream input_file("input.txt");
	// std::multimap<std::string, float> mp_input;

	// std::string temp;
	// std::getline(input_file, temp);
	// while (std::getline(input_file, temp))
	// {
	// 	//std::cout << temp << " : ";
	// 	//std::cout << temp.find(" | ") << std::endl;
	// 	int indexVL = temp.find(" | ");
	// 	std::string date = temp.substr(0, indexVL);
	// 	float value = atof((temp.substr(indexVL + 3, temp.size())).c_str());
	// 	//std::cout << "date = " << date << " value = " << value <<std::endl;
	// 	mp_input.insert(std::make_pair(date, value));
	// }

	MultimapInput mp_in("input.txt");

	// std::istream_iterator<std::string> it_input(input_file);
    // std::istream_iterator<std::string> end_input;


	//++it_input;
	//std::for_each(it_input, end_input, fillMultimap_input(data_input));

    std::multimap<std::string, float>::iterator itr2;

	
    for (itr2 = mp_in.get_mp_input().begin(); itr2 != mp_in.get_mp_input().end(); ++itr2)
	{
        std::cout << itr2->first << " => " << itr2->second << std::endl;
    }

    return 0;
}
