#include "BitcoinExchange.hpp"
#include <typeinfo>
class DisplayMultimap
{
	public:
		template <typename T>
		void operator()(T & a)
		{
			std::cout << a.first << " => " << a.second << std::endl;
		}
};

BitcoinExchange::BitcoinExchange (const std::string datas_file)
{
    std::ifstream csv_file(datas_file);
    std::istream_iterator<std::string> it_csv(csv_file);
    std::istream_iterator<std::string> it_csv_end;

	++it_csv;
	while (it_csv != it_csv_end)
	{	
		int ind_coma = (*it_csv).find(',');
		if (ind_coma == -1)
		{
			std::cout << "Error : " << (*it_csv) << std::endl;
			throw IssueWithDatas();
		}
		std::string date = (*it_csv).substr(0, ind_coma);

		std::cout << date <<std::endl;
		// if (this->date_format_is_valid(date, ',') == false)
		// {
		// 	std::cout << "Error : " << (*it_csv) << " (" << date << ")"<<std::endl;
		// 	throw IssueWithDatas();
		// }
		std::string exchange_rate_str = (*it_csv).substr(ind_coma + 1, (*it_csv).size());
		float exchange_rate = atof(exchange_rate_str.c_str());
		this->_mp_data.insert(std::make_pair(date, exchange_rate));	
		++it_csv;
	}


    //std::for_each(it_csv, it_csv_end, fillMultimap(this->_mp_data));
};

bool BitcoinExchange::value_format_is_valid (std::string value)
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

bool BitcoinExchange::date_format_is_valid(std::string date, const char sep)
{
	std::istringstream str_f(date);
	int n;
	char c;

	str_f >> n >> c;
	std::cout << "n = " << n << " c = " << c << std::endl;
	if ((n < 1900 || n > 9999) || (c != '-'))
	{
		//std::cout << "VERIF3";

		return false;
	}
	
	str_f >> n >> c;
	std::cout << "n = " << n << " c = " << c << std::endl;
	if ((n < 1 || n > 12) || (c != '-'))
	{
		//std::cout << "VERIF2";

		return false;
	}

	str_f >> n >> c;
	std::cout << "n = " << n << " c = " << c << std::endl;
	if ((n < 1 || n > 31) || (c != sep))
	{
		//std::cout << "VERIF";
		return false;
	}	

	return true;
}

std::string BitcoinExchange::extract_date (std::string line)
{
	int indexVL = line.find(" | ");
	return line.substr(0, indexVL + 2);
}

std::string BitcoinExchange::extract_value (std::string line)
{
	int indexVL = line.find(" | ");
	return line.substr(indexVL + 3, line.size());
}

float BitcoinExchange::calculate_bc_value (const std::string input_date, const float input_value)
{
	std::multimap<std::string,float>::iterator it_data = this->_mp_data.begin();
	std::multimap<std::string,float>::iterator it_data_end = this->_mp_data.end();

	while (it_data != it_data_end && input_date >= it_data->first)
		++it_data;

	if (it_data == this->_mp_data.begin())
		return input_value * it_data->second;
	
	it_data--;
	return input_value * it_data->second;
}

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
		if (line.find(" | ") == std::string::npos || this->date_format_is_valid(this->extract_date(line), '|') == false || this->value_format_is_valid(this->extract_value(line)) == false)
		{
			this->output.insert(std::make_pair(line_count, ("Error: bad input => " + line)));
		}
		else
		{
			float value = atof(this->extract_value(line).c_str());
			std::string date = this->extract_date(line);
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
				oss << date << " => " << value << " = " << calculate_bc_value(date, value);
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