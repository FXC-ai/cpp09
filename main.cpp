#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>
#include <ctime>

class DisplayMultimap
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
		fillMultimap(std::multimap<std::string, float> & mp_data) : _mp_data(mp_data) {}

		void operator()(const std::string & data)
		{
			int ind_coma = data.find(',');
			std::string date = data.substr(0, ind_coma);
			std::string exchange_rate_str = data.substr(ind_coma + 1, data.size());
			float exchange_rate = atof(exchange_rate_str.c_str());
			this->_mp_data.insert(std::make_pair(date, exchange_rate));
		}

	private:
		std::multimap<std::string, float> & _mp_data;
};

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
			return false;
		}
		str_f >> c;
	}
	return true;
}

std::string extract_date (std::string line)
{
	int indexVL = line.find(" | ");
	return line.substr(0, indexVL + 2);
}

std::string extract_value (std::string line)
{
	int indexVL = line.find(" | ");
	return line.substr(indexVL + 3, line.size());
}

float calculate_bc_value (std::multimap<std::string,float> mp_data, const std::string input_date, const float input_value)
{
	std::multimap<std::string,float>::iterator it_data = mp_data.begin();
	std::multimap<std::string,float>::iterator it_data_end = mp_data.end();

	while (it_data != it_data_end && input_date >= it_data->first)
		++it_data;

	if (it_data == mp_data.begin())
		return input_value * it_data->second;
	
	it_data--;
	return input_value * it_data->second;
}

class BitcoinExchange
{
	public :
		BitcoinExchange(const std::string datas_file);
		std::multimap<std::string, float> & get_mp_data();
		void calculate(const std::string input_file);
		void display();

	private :
    	std::multimap<std::string, float> _mp_data;
    	std::multimap<int, std::string> output;
		//float calculate_bc_value(const std::string input_date, const float input_value);

};

BitcoinExchange::BitcoinExchange (const std::string datas_file)
{
    std::ifstream csv_file(datas_file);
    std::istream_iterator<std::string> it_csv(csv_file);
    std::istream_iterator<std::string> it_csv_end;

	++it_csv;

    std::for_each(it_csv, it_csv_end, fillMultimap(this->_mp_data));
};

std::multimap<std::string, float> & BitcoinExchange::get_mp_data()
{
	return this->_mp_data;
}

void BitcoinExchange::calculate(const std::string input_file)
{
	std::ifstream input(input_file);

	std::string line;
	std::getline(input, line);


	int line_count;

	line_count = 0;
	while (std::getline(input, line))
	{
		if (line.find(" | ") == std::string::npos || date_format_is_valid(extract_date(line)) == false || value_format_is_valid(extract_value(line)) == false)
		{
			this->output.insert(std::make_pair(line_count, ("Error: bad input => " + line)));
		}
		else
		{
			float value = atof(extract_value(line).c_str());
			std::string date = extract_date(line);
			if (value < 0)
			{
				this->output.insert(std::make_pair(line_count, "Error: not a positive number."));

			}
			else if (value > 1000)
			{
				this->output.insert(std::make_pair(line_count, "Error: too large number."));
			}
			else
			{
				std::ostringstream oss;
				oss << date << " => " << value << " = " << calculate_bc_value(this->_mp_data, date, value);
				this->output.insert(std::make_pair(line_count, oss.str()));
			}
		}
		line_count++;
	}

};

void BitcoinExchange::display()
{
	std::for_each(this->output.begin(), this->output.end(), DisplayMultimap());
}




int main()
{

	BitcoinExchange bitcoin_exchange0("data.csv");
	
	//std::for_each(bitcoin_exchange0.get_mp_data().begin(), bitcoin_exchange0.get_mp_data().end(), Display() );


	// Research and calculate values

	bitcoin_exchange0.calculate("input.txt");
	bitcoin_exchange0.display();


    return 0;
}
