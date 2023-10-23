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

std::list<unsigned int> PmergeMe::get_jacobsthal()
{
	return this->_jacobsthal;
}

void PmergeMe::DisplayListToSort()
{
	for_each(this->_list_to_sort.begin(), this->_list_to_sort.end(), DisplayList());
}

void PmergeMe::DisplayJacobsthal()
{
	for_each(this->_jacobsthal.begin(), this->_jacobsthal.end(), DisplayList());
}

void PmergeMe::DisplayS()
{
	for_each(this->_S.begin(), this->_S.end(), DisplayList());
}

void PmergeMe::DisplayPend()
{
	for_each(this->_pend.begin(), this->_pend.end(), DisplayList());
}

void PmergeMe::sort_pairs()
{
	std::list<unsigned int>::iterator it = this->_list_to_sort.begin();
	std::list<unsigned int>::iterator it_2 = this->_list_to_sort.begin();

	unsigned long loop_count = this->_list_to_sort.size() / 2;
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
	int d = 0;
	std::cout << "After sorting pairs : ";
	for (std::list<unsigned int>::iterator it = this->_list_to_sort.begin(); it != this->_list_to_sort.end(); ++it)
	{
		std::cout << *it;
		if (d % 2 == 1)
		{
			std::cout << " | ";
		}
		else
		{
			std::cout << "-";
		}
		d++;
	}

}

void PmergeMe::insertion_sort_pairs ()
{
	std::list<unsigned int>::iterator it = this->_list_to_sort.begin();
	
	for (unsigned long i = 0; i < this->_list_to_sort.size(); ++i)
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
	std::cout << "After insertion_sort_pairs ";

	std::list<unsigned int>::iterator pend_it = this->_pend.begin();
	for (std::list<unsigned int>::iterator it = this->_S.begin(); it != this->_S.end(); ++it)
	{
		std::cout << *pend_it << "-" << *it << " | ";
		++pend_it;

	}
	if (this->_pend.size() % 2 == 1)
	{
		++pend_it;
		std::cout << *pend_it;
	}



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

	for (std::list<unsigned int>::iterator it = this->_jacobsthal.begin(); it != this->_jacobsthal.end(); ++it)
	{
		(*it) *= 2;
	}

	std::cout << "Jacobsthal sequence  = ";
	this->DisplayJacobsthal();
	//for_each(this->_jacobsthal.begin(), this->_jacobsthal.end(), DisplayList());

}

std::list<unsigned int> PmergeMe::index_order_generator ()
{
	std::list<unsigned int> index_order;

	unsigned long pend_size;

	pend_size = this->_list_to_sort.size();
	unsigned long index = 1;

	while (pend_size > 0)
	{

		std::list<unsigned int>::iterator j_it = this->get_element_in_list(index, this->_jacobsthal);

		while (*j_it > 0)
		{
			index_order.push_back(index + *j_it);
			*j_it--;
			
		}

		index++;
		pend_size--;
	}



	std::cout << "index_order_generator = ";
	for_each(index_order.begin(), index_order.end(), DisplayList());

	return index_order;

}

void PmergeMe::binary_sort(unsigned int n_to_insert)
{

	std::cout << n_to_insert << std::endl;

	std::cout << "S = ";
	this->DisplayS();
	std::cout << std::endl;

	// std::cout << "pend = ";
	// this->DisplayPend();
	// std::cout << std::endl;

	unsigned long size_S = this->_S.size();

	std::cout << "size_S = " << size_S << std::endl;

	//unsigned long ind_prev = 0 ;
	//unsigned long ind_next = size_S - 1;
	

	std::list<unsigned int> :: iterator start = this->_S.begin();
	std::list<unsigned int> :: iterator end = this->_S.end();

	unsigned long ind_start = 0;
	unsigned long ind_end = size_S - 1;

	//start = this->_S.end();
	//end = this->_S.begin();

	std::cout << "lkjlkjljlkj = " << *start << std::endl;

	while (start != end)
	{
		//size_S = size_S / 2;

		unsigned long ind_mid = (ind_end - ind_start) / 2;

		std::list<unsigned int> :: iterator it_mid;
		it_mid = this->get_element_in_list(ind_mid, this->_S);

		if (n_to_insert < *it_mid)
		{
			while (end != it_mid)
			{
				--end;
				--ind_end;
			}
		}

		if (n_to_insert > *it_mid)
		{
			while (start != it_mid)
			{
				++start;
				++ind_start;
			}
		}

		std::cout << *it_mid <<std::endl;

	
		++start;



	}



	//std::list<unsigned int> :: iterator middle_prev = this->get_element_in_list(ind_prev, this->_S);
	//std::list<unsigned int> :: iterator middle_next = this->get_element_in_list(ind_next, this->_S);

	//std::cout << "ind_prev = " << ind_prev << " middle = " << *middle_prev <<std::endl;
	//std::cout << "ind_next = " << ind_next << " middle = " << *middle_next <<std::endl;


	// int debug = 0;
	// while (!(n_to_insert > *middle_prev && n_to_insert < *middle_next)) /*|| middle_prev == start || middle_next == end*/
	// {
	// 	if (n_to_insert < *middle_prev && n_to_insert < *middle_next)
	// 	{
	// 		std::cout << ind_prev << " " << ind_next << " " << n_to_insert << " inferieur a "<< *middle_prev <<  " et à " << *middle_next <<std::endl;
			
	// 		unsigned long stop = ind_prev / 2;
	// 		while (ind_prev != stop)
	// 		{
	// 			ind_prev--;
	// 			ind_next--;
	// 			--middle_prev;
	// 			--middle_next;
	// 		}
	// 	}
	// 	else if (n_to_insert > *middle_prev && n_to_insert > *middle_next)
	// 	{
	// 		std::cout << ind_prev << " " << ind_next << " " << n_to_insert << " superieur a " << *middle_prev <<  " et à " << *middle_next <<std::endl;
	// 		unsigned long stop2 = ind_prev + ((size_S - ind_prev) / 2);

	// 		while (ind_prev != stop2)
	// 		{
	// 			ind_prev++;
	// 			ind_next++;
	// 			++middle_prev;
	// 			++middle_next;
	// 		}

	// 	}	
	// 	debug++;
	// }

	//std::cout << *middle_prev << " " << *middle_next << std::endl;

}