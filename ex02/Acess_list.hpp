#ifndef ACESS_LIST_HPP
#define ACESS_LIST_HPP

#include <list>

template <typename T>
class Acess_list : public std::list<T>
{
	public :
		typedef typename std::list<T>::iterator iterator;

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

#endif