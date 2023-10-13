#include "RPN.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return 0;
	}

	std::cout << argv[1] << std::endl << std::endl;

	RPN rpn(argv[1]);
	RPN rpn1(rpn);

	try
	{
		rpn1.process();
		rpn1.display();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
    return 0;
}