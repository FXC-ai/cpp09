#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <stack>
#include <filesystem>
#include <limits.h>

class RPN
{
	public :
		RPN(const std::string str);
		void process();
		void display();

		class DivisionByZero : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : division by zero.";
			}
		};

		class MaxExceeded : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : INT_MAX exceeded.";
			}
		};

		class NotADigit : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : not a digit.";
			}
		};

		class StackSizeError : public std::exception
		{
			virtual const char* what() const throw()
			{
				return "Error : too many operators.";
			}
		};


	private :
		const std::string _str;
		std::stack<long> stack_process;
		void process_add();
		void process_min();
		void process_div();
		void process_mul();
		void process_push(const char c);
};

RPN::RPN(const std::string str) : _str(str) {};


void RPN::process_push(const char c)
{
	if (std::isdigit(c) == false)
	{
		throw NotADigit();
	}
	this->stack_process.push(c - '0');
}



void RPN::process_add()
{
	long op0;
	long op1;
	long r;
	
	if (this->stack_process.size() <= 1)
	{
		throw StackSizeError();
	}
	op0 = this->stack_process.top();
	this->stack_process.pop();
	op1 = this->stack_process.top();
	this->stack_process.pop();
	r = op1 + op0;
	if (r < INT_MIN || r > INT_MAX)
	{
		throw MaxExceeded();
	}
	this->stack_process.push(r);
}

void RPN::process_min()
{
	long op0;
	long op1;
	long r;
	
	if (this->stack_process.size() <= 1)
	{
		throw StackSizeError();
	}
	op0 = this->stack_process.top();
	this->stack_process.pop();
	op1 = this->stack_process.top();
	this->stack_process.pop();
	r = op1 - op0;
	if (r < INT_MIN || r > INT_MAX)
	{
		throw MaxExceeded();
	}
	this->stack_process.push(r);
}

void RPN::process_mul()
{
	long op0;
	long op1;
	long r;
	
	if (this->stack_process.size() <= 1)
	{
		throw StackSizeError();
	}
	op0 = this->stack_process.top();
	this->stack_process.pop();
	op1 = this->stack_process.top();
	this->stack_process.pop();
	r = op1 * op0;
	if (r < INT_MIN || r > INT_MAX)
	{
		throw MaxExceeded();
	}
	this->stack_process.push(r);
}

void RPN::process_div()
{
	long op0;
	long op1;
	long r;
	
	if (this->stack_process.size() <= 1)
	{
		throw StackSizeError();
	}
	op0 = this->stack_process.top();
	this->stack_process.pop();
	op1 = this->stack_process.top();
	this->stack_process.pop();
	if (op0 == 0)
	{
		throw DivisionByZero();
	}
	r = op1 / op0;
	if (r < INT_MIN || r > INT_MAX)
	{
		throw MaxExceeded();
	}
	this->stack_process.push(r);
}

void RPN::display()
{
	if (this->stack_process.size() == 1)
	{
		std::cout << "Result = " << this->stack_process.top() << std::endl;
	}
	else
	{
		std::cout << "Stack is not empty : ";
		while (this->stack_process.empty() == false)
		{
			std::cout << this->stack_process.top() << " ";
			this->stack_process.pop();
		}
		std::cout << std::endl;
	}
}

void RPN::process ()
{
	std::istringstream str_stream(this->_str);

	char c;
	int loop_c = 0;

	while (str_stream >> c)
	{
		switch (c)
		{
			case '+' :
				this->process_add();
				break;
			case '-' :
				this->process_min();
				break;
			case '*' :
				this->process_mul();
				break;
			case '/' :
				this->process_div();
				break;
			default :
				this->process_push(c);
				break;
		}	
		loop_c ++;
	}
};

int main(int argc, char* argv[])
{

	if (argc != 2)
	{
		std::cerr << "Error" << std::endl;
		return 0;
	}

	std::cout << argv[1] << std::endl << std::endl;

	RPN rpn(argv[1]);

	try
	{
		rpn.process();
		rpn.display();
		
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
    return 0;
}