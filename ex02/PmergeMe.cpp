#include "PmergeMe.hpp"

class DisplayList
{
	public :
		void operator()(unsigned int a)
		{
			std::cout << a << " ";
		}
};

class SumList
{
	public :
		SumList() : _sum_list(0){};
		unsigned long long get_sum_list()
		{
			return this->_sum_list;
		}

		void operator()(unsigned int a)
		{
			this->_sum_list += a;
		}

	private :
		unsigned long long _sum_list;

};

PmergeMe::PmergeMe(std::list<unsigned int>list_to_sort) : _list_to_sort(list_to_sort){};

std::list<unsigned int> PmergeMe::get_list_to_sort()
{
	return this->_list_to_sort;
}

std::list<unsigned int> PmergeMe::get_list_sorted_pairs()
{
	return this->_list_sorted_pairs;
}

std::list<unsigned int> PmergeMe::get_S()
{
	return this->_S;
}

std::list<unsigned int> PmergeMe::get_pend()
{
	return this->_pend;
}

std::list<unsigned int> PmergeMe::get_jacobsthal()
{
	return this->_jacobsthal;
}

void PmergeMe::diplayList(std::list<unsigned int> list_to_display)
{
	for_each(list_to_display.begin(), list_to_display.end(), DisplayList());
}

void PmergeMe::sort_pairs()
{
	this->_list_sorted_pairs = this->_list_to_sort;

	std::list<unsigned int>::iterator it = this->_list_sorted_pairs.begin();
	std::list<unsigned int>::iterator it_2 = this->_list_sorted_pairs.begin();

	unsigned long loop_count = this->_list_sorted_pairs.size() / 2;
	it_2++;

	while (loop_count > 0)
	{	
		if (*it_2 < *it)
		{	
			this->switch_it(it, it_2);
		}
		++it;
		++it;
		++it_2;
		++it_2;
		loop_count--;
	}

	//DEBUG
	// int d = 0;
	// std::cout << "After sorting pairs : ";
	// for (std::list<unsigned int>::iterator it = this->_list_sorted_pairs.begin(); it != this->_list_sorted_pairs.end(); ++it)
	// {
	// 	std::cout << *it;
	// 	if (d % 2 == 1)
	// 	{
	// 		std::cout << " | ";
	// 	}
	// 	else
	// 	{
	// 		std::cout << "-";
	// 	}
	// 	d++;
	// }

}

void PmergeMe::insertion_sort_pairs ()
{
	std::list<unsigned int>::iterator it = this->_list_sorted_pairs.begin();
	
	for (unsigned long i = 0; i < this->_list_sorted_pairs.size(); ++i)
	{
		if (i%2 == 1)
		{
			this->_S.push_back(*it);
		}
		else
		{
			this->_pend.push_back(*it);
		}
		++it;
	}

	for (unsigned long index = 1; index < this->_S.size(); ++index)
	{
		std::list<unsigned int>::iterator start = this->_S.begin();
		std::list<unsigned int>::iterator it_current = this->get_element_in_list(index, this->_S);
		std::list<unsigned int>::iterator it_mover = this->get_element_in_list(index - 1, this->_S);

		std::list<unsigned int>::iterator it_current_p = this->get_element_in_list(index, this->_pend);
		std::list<unsigned int>::iterator it_mover_p = this->get_element_in_list(index - 1, this->_pend);

		while (*it_current < *it_mover && it_mover != start)
		{
			--it_mover_p;
			--it_mover;
		}

		if (index == 1 && *it_current < *it_mover )
		{
			this->switch_it(it_mover_p, it_current_p);
			this->switch_it(it_mover, it_current);
		}
		else if (it_mover == start && *it_current < *start)
		{
			this->_pend.push_front(*it_current_p);
			this->_pend.erase(it_current_p);
			this->_S.push_front(*it_current);
			this->_S.erase(it_current);
		}
		else
		{
			this->_pend.insert(++it_mover_p, *it_current_p);
			this->_pend.erase(it_current_p);
			this->_S.insert(++it_mover, *it_current);
			this->_S.erase(it_current);
		}
	}

	//Display for debug
	// std::cout << "After insertion_sort_pairs ";
	// std::cout << std::endl;

	// std::cout << "S : ";
	// for_each(this->_S.begin(), this->_S.end(), DisplayList());
	// std::cout << std::endl;
	// std::cout << "Pend : ";
	// for_each(this->_pend.begin(), this->_pend.end(), DisplayList());
	// std::cout << std::endl;


}

void swap_in_list(std::list<unsigned int>::iterator & it, std::list<unsigned int>::iterator & it_2)
{
	unsigned int temp;

	temp = *it;
	*it = *it_2;
	*it_2 = temp;
};

void PmergeMe::switch_it(std::list<unsigned int>::iterator & it, std::list<unsigned int>::iterator & it_2)
{
	unsigned int temp;

	temp = *it;
	*it = *it_2;
	*it_2 = temp;
};

std::list<unsigned int>::iterator PmergeMe::get_element_in_list(unsigned long ind, std::list<unsigned int> & list)
{
	std::list<unsigned int>::iterator it;
	it = list.begin();

	while (ind > 0)
	{
		it++;
		ind--;
	}
	return it;
}

void PmergeMe::jacobsthal_generator ()
{
	this->_jacobsthal.clear();
	this->_jacobsthal.push_back(0);
	this->_jacobsthal.push_back(1);
	this->_jacobsthal.push_back(1);

	SumList sum = for_each(this->_jacobsthal.begin(), this->_jacobsthal.end(), SumList());


	unsigned long i;

	i = 2;

	while ((sum.get_sum_list()*2) <= this->_list_to_sort.size())
	{
		std::list<unsigned int>::iterator Jn_2 = this->get_element_in_list(i - 1, this->_jacobsthal); 
		std::list<unsigned int>::iterator Jn_1 = this->get_element_in_list(i, this->_jacobsthal); 

		unsigned int r = *Jn_1 + (2 * (*Jn_2));

		this->_jacobsthal.push_back(r);

		sum = for_each(this->_jacobsthal.begin(), this->_jacobsthal.end(), SumList());

		++i;
	}

	// for (std::list<unsigned int>::iterator it = this->_jacobsthal.begin(); it != this->_jacobsthal.end(); ++it)
	// {
	// 	(*it) *= 2;
	// }

	// std::cout << "Jacobsthal sequence  = ";
	// this->DisplayJacobsthal();


}

std::list<unsigned int> PmergeMe::index_order_generator ()
{

	this->jacobsthal_generator();
	std::list<unsigned int> index_order;

	const unsigned long pend_size = this->_pend.size();

	if (pend_size == 1)
	{
		index_order.push_back(0);
		return index_order;
	}

	if (pend_size == 2)
	{
		index_order.push_back(0);
		index_order.push_back(1);
		return index_order;
	}

	if (pend_size == 3)
	{

		index_order.push_back(0);
		index_order.push_back(1);
		index_order.push_back(2);
		return index_order;
	}

	index_order.push_back(0);
	index_order.push_back(2);
	index_order.push_back(1);

	unsigned long index_lowest = *(max_element(index_order.begin(), index_order.end()));
	unsigned long index_highest = *(max_element(index_order.begin(), index_order.end())) + *(this->get_element_in_list(1, this->_jacobsthal));
	
	int count = 1;
	while (index_order.size() != pend_size)
	{

		index_lowest = *(max_element(index_order.begin(), index_order.end()));
		index_highest = *(max_element(index_order.begin(), index_order.end())) + *(this->get_element_in_list(count, this->_jacobsthal));
		
		if (index_highest >= pend_size)
		{
			index_highest = pend_size - 1;
		}
		while (index_lowest < index_highest)
		{
			index_order.push_back(index_highest);
			index_highest--;
		}
		count++;
	}

	if (index_order.size() != pend_size)
	{
		std::cerr << "Error : index_order.size() != pend_size" << std::endl;
	}

	// std::cout << "index_order = ";
	// for_each(index_order.begin(), index_order.end(), DisplayList());

	return index_order;

}

unsigned long PmergeMe::binary_sort(unsigned int n_to_insert)
{
	unsigned long left = 0;
	unsigned long right = this->_S.size();
	unsigned long mid = 0;

	while (left < right)
	{
		mid = left + (right - left) / 2;

		if (*(this->get_element_in_list(mid, this->_S)) < n_to_insert)
		{
			left = mid + 1;
		}
		else
		{
			right = mid;
		}
	}

	//std::cout << "result = " << mid <<std::endl;
	return left;
}

void PmergeMe::insertion_sort()
{

	std::list<unsigned int> index_order = this->index_order_generator();

	std::cout << std::endl;

	unsigned int index = 0;

	while (index_order.size() > 0)
	{
		index = index_order.front();

		unsigned int value_to_insert = *(this->get_element_in_list(index, this->_pend));

		unsigned long ind_to_insert = this->binary_sort(value_to_insert);

		std::list<unsigned int>::iterator it_insertion_S = this->get_element_in_list(ind_to_insert, this->_S);

		this->_S.insert(it_insertion_S, value_to_insert);

		index_order.pop_front();

		// std::cout << "S = ";
		// this->DisplayS();
		// std::cout << std::endl;
	}
	// std::cout << "S = ";
	// this->DisplayS();
	// std::cout << std::endl;

	this->check_sort(this->_S);
}


bool PmergeMe::check_sort(std::list<unsigned int>list_to_check)
{
	std::list<unsigned int>::iterator start = list_to_check.begin();
	std::list<unsigned int>::iterator it_mover = list_to_check.begin();
	std::list<unsigned int>::iterator end = list_to_check.end();

	++it_mover;
	for (; it_mover != end; ++it_mover)
	{
		//std::cout << "Je compare " << *start << " avec " << *it_mover <<std::endl;
		if (*start > *it_mover)
		{	
			std::cout << "NON SORTED LIST " << *start << " " << *it_mover <<std::endl;
			return false;
		}
		++start;
	}

	std::cout << "LISTE SORTED" <<std::endl;
	return true;
}
