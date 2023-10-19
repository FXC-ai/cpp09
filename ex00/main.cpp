#include "BitcoinExchange.hpp"

int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		std::cerr << "Error: could not open file." <<std::endl;
		return 0;
	}

	std::ifstream file;
	file.open(argv[1]);

	if(!file)
	{
		std::cerr << "Error: could not open file : " << argv[1] <<std::endl;
		return 0;
	}
	else
	{
		file.close();
	}


	std::cout << "\033[1;34m" << "TEST 0 :" << "\033[0m" << std::endl;
	try
	{
		BitcoinExchange bitcoin_exchange("data.csv");
		bitcoin_exchange.calculate(argv[1]);
		bitcoin_exchange.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;


	std::cout << "\033[1;34m" << "TEST 1 : BitcoinExchange() :" << "\033[0m" << std::endl;
	try
	{
		BitcoinExchange bitcoin_exchange;
		bitcoin_exchange.calculate(argv[1]);
		bitcoin_exchange.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;

	std::cout << "\033[1;34m" << "TEST 2 : BitcoinExchange(const BitcoinExchange & src) :" << "\033[0m" << std::endl;
	try
	{
		BitcoinExchange bitcoin_exchange0("data.csv");
		bitcoin_exchange0.calculate(argv[1]);
		BitcoinExchange bitcoin_exchange1(bitcoin_exchange0);
		bitcoin_exchange1.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;

	std::cout << "\033[1;34m" << "TEST 3 : BitcoinExchange & operator=(const BitcoinExchange & rhs) :" << "\033[0m" << std::endl;
	try
	{
		BitcoinExchange bitcoin_exchange0;
		BitcoinExchange bitcoin_exchange1("data.csv");
		bitcoin_exchange1.calculate(argv[1]);

		bitcoin_exchange0 = bitcoin_exchange1;

		bitcoin_exchange0.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;

	std::cout << "\033[1;34m" << "TEST 4 : test with a corrupted database :" << "\033[0m" << std::endl;
	try
	{
		BitcoinExchange bitcoin_exchange0;
		BitcoinExchange bitcoin_exchange1("data_with_errors/existepas.csv");
		bitcoin_exchange1.calculate(argv[1]);

		bitcoin_exchange0 = bitcoin_exchange1;

		bitcoin_exchange0.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;

	try
	{
		BitcoinExchange bitcoin_exchange0;
		BitcoinExchange bitcoin_exchange1("data_with_errors/data_with_errors1.csv");
		bitcoin_exchange1.calculate(argv[1]);

		bitcoin_exchange0 = bitcoin_exchange1;

		bitcoin_exchange0.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;

	try
	{
		BitcoinExchange bitcoin_exchange0;
		BitcoinExchange bitcoin_exchange1("data_with_errors/data_with_errors2.csv");
		bitcoin_exchange1.calculate(argv[1]);

		bitcoin_exchange0 = bitcoin_exchange1;

		bitcoin_exchange0.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;


	try
	{
		BitcoinExchange bitcoin_exchange0;
		BitcoinExchange bitcoin_exchange1("data_with_errors/data_with_errors3.csv");
		bitcoin_exchange1.calculate(argv[1]);

		bitcoin_exchange0 = bitcoin_exchange1;

		bitcoin_exchange0.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	std::cout << std::endl;

    return 0;
}
