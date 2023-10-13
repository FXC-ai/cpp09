#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stack>
#include <filesystem>


// class RPN
// {
// 	public :
// 		RPN(const std::string str);
// 		void process();

// 	private :
// 		const std::string _str;
// 		std::stack<long> stack_process;
// };


// RPN::RPN(const std::string str) : _str(str) {};



void process (std::string str)
{

	std::stack<long> stack_process;

	std::istringstream str_stream(str);

	char c;
	int loop_c = 0;
	long op0;
	long op1;

	while (str_stream >> c)
	{

		switch (c)
		{
			case 43 :
				if (stack_process.size() <= 1)
				{
					throw std::exception();
				}
				op0 = stack_process.top();
				stack_process.pop();
				op1 = stack_process.top();
				stack_process.pop();
				stack_process.push((op1 + op0));
				break;
			case 45 :
				if (stack_process.size() <= 1)
				{
					throw std::exception();
				}
				op0 = stack_process.top();
				stack_process.pop();
				op1 = stack_process.top();
				stack_process.pop();
				stack_process.push((op1 - op0));
				break;
			case 42 :
				if (stack_process.size() <= 1)
				{
					throw std::exception();
				}
				op0 = stack_process.top();
				stack_process.pop();
				op1 = stack_process.top();
				stack_process.pop();
				stack_process.push((op1 * op0));
				break;
			case 47 :
				if (stack_process.size() <= 1)
				{
					throw std::exception();
				}
				op0 = stack_process.top();
				stack_process.pop();
				op1 = stack_process.top();
				stack_process.pop();
				if (op0 == 0)
				{
					throw std::exception();
				}
				stack_process.push((op1 / op0));
				break;
			default :
				stack_process.push(c - '0');
				break;

		}
		
		loop_c ++;
	}
	
	if (stack_process.size() == 1)
	{
		std::cout << "result = " << stack_process.top() << std::endl;
	}
	else
	{
		std::cout << "Stack is not empty : ";
		while (stack_process.empty() == false)
		{
			std::cout << stack_process.top() << " ";
			stack_process.pop();
		}
		std::cout << std::endl;
	}
};

// * : 42
// / : 47
// - : 45
// + : 43

int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return 0;
	}

	std::cout << argv[1] << std::endl << std::endl;

	std::stack<int> stack_process;

	std::istringstream str_stream(argv[1]);

	// char c;
	// int loop_c = 0;
	// while (str_stream >> c)
	// {
	// 	std::cout << loop_c << " : " << c << std::endl;
	// 	stack_process.push(c);
	// 	loop_c ++;
	// }

	// std::cout << std::endl;
	try
	{
		process(argv[1]);
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	// std::cout << std::endl;

	// while (stack_process.empty() == false)
	// {
	// 	std::cout << static_cast<char> (stack_process.top())<< " : " << stack_process.top() << std::endl;
	// 	stack_process.pop();
	// }


    return 0;
}