#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <filesystem>

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

		bool value_format_is_valid (std::string value);
		bool date_format_is_valid(std::string date);
		std::string extract_date (std::string line);
		std::string extract_value (std::string line);

		float calculate_bc_value(const std::string input_date, const float input_value);

};

#endif