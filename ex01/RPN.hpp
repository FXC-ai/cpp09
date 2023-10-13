#ifndef RPN_HPP
#define RPN_HPP

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
		RPN();
		RPN(const std::string str);
		RPN(const RPN &src);
		void process();
		void display();
		const std::string get_str() const;
		std::stack<long> get_process_stack() const;
		RPN & operator=(const RPN & rhs);


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
		std::string _str;
		std::stack<long> _stack_process;
		void process_add();
		void process_min();
		void process_div();
		void process_mul();
		void process_push(const char c);
};


#endif