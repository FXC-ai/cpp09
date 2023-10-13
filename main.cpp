#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>

class Display
{
	public:
		template <typename T>
		void operator()(T & a)
		{
			std::cout << a.first << " => " << a.second << std::endl;
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
		MultimapInput(const std::string fileName, std::multimap<std::string, float> & mp_input);

	private:
		const std::string _fileName;
		std::multimap<std::string, float> & _mp_input;
};

MultimapInput::MultimapInput(const std::string fileName, std::multimap<std::string, float> & mp_input) : _fileName(fileName), _mp_input(mp_input)
{
	std::ifstream input_file(this->_fileName);

	std::string temp;
	std::getline(input_file, temp);
	while (std::getline(input_file, temp))
	{
		int indexVL = temp.find(" | ");
		float value = 0;
		std::string date;
		if (indexVL == 10)
		{
			date = temp.substr(0, indexVL);
			value = atof((temp.substr(indexVL + 3, temp.size())).c_str());
			this->_mp_input.insert(std::make_pair(date, value));
		}
		else
		{
			date = temp;
			this->_mp_input.insert(std::make_pair(date, value));
		}
	}

};

// class BitcoinExchange
// {
// 	public :


// 	private :
//     	std::multimap<std::string, float> mp_data;
// 		std::multimap<std::string, float> mp_input;



// }

bool date_format_is_valid(std::string date)
{
	std::istringstream str_f(date);
	int n;
	char c;

	str_f >> n >> c;
	if ((n < 1900 || n > 9999) || (c != '-'))
	{
		return false;
	}
	
	str_f >> n >> c;
	if ((n < 1 || n > 12) || (c != '-'))
	{
		return false;
	}
	//std::cout << "n = " << n << " c = " << c << std::endl;

	str_f >> n >> c;
	if ((n < 1 || n > 31) || (c != '|'))
	{
		return false;
	}	
	//std::cout << "n = " << n << " c = " << c << std::endl;

	return true;
}

bool value_format_is_valid (std::string value)
{
	std::istringstream str_f(value);
	char c;
	
	str_f >> c;
	if (c == '-')
	{
		str_f >> c;
	}

	while (str_f)
	{
		if ((c < '0' || c > '9') && c != '.')
		{
			//std::cout << "ba non la c est pas un float mec (" << c << ')' <<std::endl;
			return false;
		}
		str_f >> c;
	}
	return true;
}

int main()
{
	// Date_tm("2022-12-29");
	// std::string date1 = "2021-02-31";
	// std::string date2 = "2021-01-20";

	// std::cout << "T1 =" << (date1 < date2) << std::endl;
	// std::cout << "T2 =" << (date2 < date1) << std::endl;

    std::ifstream csv_file("data.csv");
    std::istream_iterator<std::string> it(csv_file);
    std::istream_iterator<std::string> end;
    std::multimap<std::string, float> mp_data;
    
	++it;

    std::for_each(it, end, fillMultimap(mp_data));


	// std::for_each(mp_data.begin(), mp_data.end(), Display());

	// std::multimap<std::string, float> mp_input;
	// MultimapInput("input.txt", mp_input);
	// std::for_each(mp_input.begin(), mp_input.end(), Display());


	std::ifstream input_file("input.txt");

	std::string line;
	std::getline(input_file, line);
	while (std::getline(input_file, line))
	{
		int indexVL = line.find(" | ");
		float value;

		
		if (line.find(" | ") == std::string::npos || date_format_is_valid(line) == false || value_format_is_valid(line.substr(indexVL + 3, line.size())) == false)
		{
			std::cout << "Error: " << "bad input => " << line <<std::endl;
		}
		else
		{
			value = atof((line.substr(indexVL + 3, line.size())).c_str());
			if (value < 0)
			{
				std::cout << "Error: " << "not a positive number." <<std::endl;
			}
			else if (value > 1000)
			{
				std::cout << "Error: " << "too large number." <<std::endl;
			}
			else
			{
				//std::cout << line << " " << value << " => ";
				std::string date = line.substr(0, indexVL);
				//std::multimap<std::string,float>::iterator start = mp_data.begin()


				//std::cout << "date = [" << date << "]"<<std::endl;
				for (std::multimap<std::string,float>::iterator start = mp_data.begin(); start != mp_data.end(); ++start)
				{
					if (date <= start->first)
					{
						//std::cout << "Je cherche "<< date;
						start --;
						//std::cout << " Je trouve : " << start->first <<std::endl;

						float result = value * start->second;
						std::cout << date << " => " << value << " = " << result << std::endl;
						break;
					}
				}
				// if (start == end)
				// {
				// 	std::cout << "La date est trop early." << std::cout;
				// }
			}


		}


	}

	//value_format_is_valid("| 2");

    return 0;
}
