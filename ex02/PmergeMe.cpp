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

PmergeMe::PmergeMe(std::deque<unsigned int>list_to_sort) : _list_to_sort(list_to_sort){};

std::deque<unsigned int> PmergeMe::get_deque_to_sort()
{
	return this->_list_to_sort;
}

std::deque<unsigned int> PmergeMe::get_deque_sorted_pairs()
{
	return this->_list_sorted_pairs;
}

std::deque<unsigned int> PmergeMe::get_S_d()
{
	return this->_S;
}

std::deque<unsigned int> PmergeMe::get_pend_d()
{
	return this->_pend;
}


void PmergeMe::diplayL_deq(std::deque<unsigned int> list_to_display)
{
	for_each(list_to_display.begin(), list_to_display.end(), DisplayList());
}

void PmergeMe::sort_pairs_deq()
{
	this->_list_sorted_pairs = this->_list_to_sort;

	std::deque<unsigned int>::iterator it = this->_list_sorted_pairs.begin();
	std::deque<unsigned int>::iterator it_2 = this->_list_sorted_pairs.begin();

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
	// for (std::deque<unsigned int>::iterator it = this->_list_sorted_pairs.begin(); it != this->_list_sorted_pairs.end(); ++it)
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

void PmergeMe::insertion_sort_pairs_deq ()
{
	std::deque<unsigned int>::iterator it = this->_list_sorted_pairs.begin();
	
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

	// std::cout << "S : ";
	// for_each(this->_S.begin(), this->_S.end(), DisplayList());
	// std::cout << std::endl;
	// std::cout << "Pend : ";
	// for_each(this->_pend.begin(), this->_pend.end(), DisplayList());
	// std::cout << std::endl;


	for(unsigned long i = 1; i < this->_S.size(); ++i) 
	{
		unsigned int key = this->_S[i];
		unsigned int key_p = this->_pend[i];
		int j = i - 1;

		while(j >= 0 && this->_S[j] > key) 
		{
			this->_S[j + 1] = this->_S[j];
			this->_pend[j + 1] = this->_pend[j];
			j--;

		}
		this->_S[j + 1] = key;
		this->_pend[j + 1] = key_p;
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

void swap_in_list(std::deque<unsigned int>::iterator & it, std::deque<unsigned int>::iterator & it_2)
{
	unsigned int temp;

	temp = *it;
	*it = *it_2;
	*it_2 = temp;
};

void PmergeMe::switch_it(std::deque<unsigned int>::iterator & it, std::deque<unsigned int>::iterator & it_2)
{
	unsigned int temp;

	temp = *it;
	*it = *it_2;
	*it_2 = temp;
};

std::deque<unsigned int>::iterator PmergeMe::get_element_in_list(unsigned long ind, std::deque<unsigned int> & list)
{
	std::deque<unsigned int>::iterator it;
	it = list.begin();

	while (ind > 0)
	{
		it++;
		ind--;
	}
	return it;
}

std::deque<unsigned int> PmergeMe::jacobsthal_generator ()
{
	std::deque<unsigned int> jacobsthal;

	jacobsthal.clear();
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);
	jacobsthal.push_back(1);

	SumList sum = for_each(jacobsthal.begin(), jacobsthal.end(), SumList());

	unsigned long i = 2;
	while ((sum.get_sum_list()*2) <= this->_list_to_sort.size())
	{
		std::deque<unsigned int>::iterator Jn_2 = this->get_element_in_list(i - 1, jacobsthal); 
		std::deque<unsigned int>::iterator Jn_1 = this->get_element_in_list(i, jacobsthal); 

		unsigned int r = *Jn_1 + (2 * (*Jn_2));

		jacobsthal.push_back(r);

		sum = for_each(jacobsthal.begin(), jacobsthal.end(), SumList());

		++i;
	}

	for (std::deque<unsigned int>::iterator it = jacobsthal.begin(); it != jacobsthal.end(); ++it)
	{
		(*it) *= 2;
	}

	// std::cout << "Jacobsthal sequence  = ";
	// for_each(jacobsthal.begin(), jacobsthal.end(), DisplayList());

	// this->DisplayJacobsthal();
	
	
	return jacobsthal;

}

std::deque<unsigned int> PmergeMe::index_order_generator ()
{

	std::deque<unsigned int> jacobsthal = this->jacobsthal_generator();

	//this->diplayList(jacobsthal);


	std::deque<unsigned int> index_order;

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
	unsigned long index_highest = *(max_element(index_order.begin(), index_order.end())) + *(this->get_element_in_list(1, jacobsthal));
	
	int count = 1;
	while (index_order.size() != pend_size)
	{

		index_lowest = *(max_element(index_order.begin(), index_order.end()));
		index_highest = *(max_element(index_order.begin(), index_order.end())) + *(this->get_element_in_list(count, jacobsthal));
		
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

void PmergeMe::binary_insertion_sort_deq()
{

	std::deque<unsigned int> index_order = this->index_order_generator();

	// std::cout << "index_order = ";
	// for_each(index_order.begin(), index_order.end(), DisplayList());
	// std::cout << std::endl;

	unsigned int index = 0;

	while (index_order.size() > 0)
	{
		index = index_order.front();

		unsigned int value_to_insert = *(this->get_element_in_list(index, this->_pend));

		unsigned long ind_to_insert = this->binary_sort(value_to_insert);

		std::deque<unsigned int>::iterator it_insertion_S = this->get_element_in_list(ind_to_insert, this->_S);

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

bool PmergeMe::check_sort(std::deque<unsigned int>list_to_check)
{
	std::deque<unsigned int>::iterator start = list_to_check.begin();
	std::deque<unsigned int>::iterator it_mover = list_to_check.begin();
	std::deque<unsigned int>::iterator end = list_to_check.end();

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

void PmergeMe::sort_deq()
{
	this->sort_pairs_deq();


	this->insertion_sort_pairs_deq();


	this->binary_insertion_sort_deq();

}