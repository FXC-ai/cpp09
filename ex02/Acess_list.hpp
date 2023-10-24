#ifndef ACESS_LIST_HPP
#define ACESS_LIST_HPP

#include <list>

template <typename T>
class Acess_list : public std::deque<T>
{
	public :
		typedef typename std::deque<T>::iterator iterator;

		iterator operator[](unsigned long index)
		{
			iterator it = this->begin();
			iterator end = this->end();
			while (index>0 && it != end)
			{
				it++;
				index--;
			}
			return it;
		}



};

	// Acess_list<int> AL_test;


	// AL_test.push_back(18);
	// AL_test.push_back(12);
	// AL_test.push_back(16);
	// AL_test.push_back(98);
	// AL_test.push_back(19);

	// Acess_list<int>::iterator it = AL_test[20];

	// std::cout << *it << std::endl;

#endif