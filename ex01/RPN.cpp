#include "RPN.hpp"

RPN::RPN() : _str(""){};

RPN::RPN(const RPN &src) : _str(src.get_str())
{
	this->_stack_process = src.get_process_stack();
}

RPN::RPN(const std::string str) : _str(str) {};

const std::string RPN::get_str() const
{
	return this->_str;
}

std::stack<long> RPN::get_process_stack() const
{
	return this->_stack_process;
};

RPN & RPN::operator=(const RPN &rhs)
{	
	if (this != &rhs)
	{
		this->_str = rhs.get_str();
		this->_stack_process = rhs.get_process_stack();
	}
	return *this;
}

void RPN::process_push(const char c)
{
	if (std::isdigit(c) == false)
	{
		throw NotADigit();
	}
	this->_stack_process.push(c - '0');
}

void RPN::process_add()
{
	long op0;
	long op1;
	long r;
	
	if (this->_stack_process.size() <= 1)
	{
		throw StackSizeError();
	}
	op0 = this->_stack_process.top();
	this->_stack_process.pop();
	op1 = this->_stack_process.top();
	this->_stack_process.pop();
	r = op1 + op0;
	if (r < INT_MIN || r > INT_MAX)
	{
		throw MaxExceeded();
	}
	this->_stack_process.push(r);
}

void RPN::process_min()
{
	long op0;
	long op1;
	long r;
	
	if (this->_stack_process.size() <= 1)
	{
		throw StackSizeError();
	}
	op0 = this->_stack_process.top();
	this->_stack_process.pop();
	op1 = this->_stack_process.top();
	this->_stack_process.pop();
	r = op1 - op0;
	if (r < INT_MIN || r > INT_MAX)
	{
		throw MaxExceeded();
	}
	this->_stack_process.push(r);
}

void RPN::process_mul()
{
	long op0;
	long op1;
	long r;
	
	if (this->_stack_process.size() <= 1)
	{
		throw StackSizeError();
	}
	op0 = this->_stack_process.top();
	this->_stack_process.pop();
	op1 = this->_stack_process.top();
	this->_stack_process.pop();
	r = op1 * op0;
	if (r < INT_MIN || r > INT_MAX)
	{
		throw MaxExceeded();
	}
	this->_stack_process.push(r);
}

void RPN::process_div()
{
	long op0;
	long op1;
	long r;
	
	if (this->_stack_process.size() <= 1)
	{
		throw StackSizeError();
	}
	op0 = this->_stack_process.top();
	this->_stack_process.pop();
	op1 = this->_stack_process.top();
	this->_stack_process.pop();
	if (op0 == 0)
	{
		throw DivisionByZero();
	}
	r = op1 / op0;
	if (r < INT_MIN || r > INT_MAX)
	{
		throw MaxExceeded();
	}
	this->_stack_process.push(r);
}

void RPN::display()
{
	if (this->_stack_process.size() == 1)
	{
		std::cout << "Result = " << this->_stack_process.top() << std::endl;
	}
	else
	{
		std::cout << "Stack is not empty : ";
		while (this->_stack_process.empty() == false)
		{
			std::cout << this->_stack_process.top() << " ";
			this->_stack_process.pop();
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