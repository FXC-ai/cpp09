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

	if (file)
	{
		file.close();
		BitcoinExchange bitcoin_exchange0("data.csv");
		bitcoin_exchange0.calculate(argv[1]);
		bitcoin_exchange0.display();
		
	}
	else
	{
		std::cerr << "Error: could not open file." <<std::endl;

	}
    return 0;
}
