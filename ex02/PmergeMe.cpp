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
	int d = 0;
	std::cout << "After sorting pairs : ";
	for (std::list<unsigned int>::iterator it = this->_list_sorted_pairs.begin(); it != this->_list_sorted_pairs.end(); ++it)
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

	// for_each(this->_S.begin(), this->_S.end(), DisplayList());
	// std::cout << std::endl;
	// for_each(this->_pend.begin(), this->_pend.end(), DisplayList());
	// std::cout << std::endl;

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
	std::cout << std::endl;

	std::cout << "S : ";
	for_each(this->_S.begin(), this->_S.end(), DisplayList());
	std::cout << std::endl;
	std::cout << "Pend : ";
	for_each(this->_pend.begin(), this->_pend.end(), DisplayList());
	std::cout << std::endl;


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

	unsigned long pend_size = this->_pend.size();

	std::cout << "pend_size = " << pend_size << std::endl;

	index_order.push_back(0);
	index_order.push_back(2);
	index_order.push_back(1);


	unsigned long index_lowest = *(max_element(index_order.begin(), index_order.end()));
	unsigned long index_highest = *(max_element(index_order.begin(), index_order.end())) + *(this->get_element_in_list(1, this->_jacobsthal));
	std::cout << "index_lowest = " << index_lowest << std::endl;
	std::cout << "index_highest = " << index_highest << std::endl;
	
	if (index_highest >= pend_size)
	{
		index_highest = pend_size - 1;
	}
	while (index_lowest < index_highest)
	{
		index_order.push_back(index_highest);
		index_highest--;
	}

	index_lowest = *(max_element(index_order.begin(), index_order.end()));
	index_highest = *(max_element(index_order.begin(), index_order.end())) + *(this->get_element_in_list(2, this->_jacobsthal));
	std::cout << "index_lowest = " << index_lowest << std::endl;
	std::cout << "index_highest = " << index_highest << std::endl;

	if (index_highest >= pend_size)
	{
		index_highest = pend_size - 1;
	}
	while (index_lowest < index_highest)
	{
		index_order.push_back(index_highest);
		index_highest--;
	}

	index_lowest = *(max_element(index_order.begin(), index_order.end()));
	index_highest = *(max_element(index_order.begin(), index_order.end())) + *(this->get_element_in_list(3, this->_jacobsthal));
	std::cout << "index_lowest = " << index_lowest << std::endl;
	std::cout << "index_highest = " << index_highest << std::endl;


	if (index_highest >= pend_size)
	{
		index_highest = pend_size - 1;
	}
	while (index_lowest < index_highest)
	{
		index_order.push_back(index_highest);
		index_highest--;
	}


	//std::cout << "index lowest " << index_lowest << " -> " << *(this->get_element_in_list(index_lowest, index_order)) << std::endl;

	//index_highest =  + *(this->get_element_in_list(2, this->_jacobsthal));



	//index_order.push_back(*(this->get_element_in_list(1, this->_jacobsthal)));




	//unsigned long jacobsthal_size;

	//jacobsthal_size = this->_jacobsthal.size();
	
	//unsigned long index = 3;





	// unsigned long pend_size;

	// pend_size = this->_pend.size();
	// unsigned long index = 1;

	// //y_{4},y_{3},y_{6},y_{5},y_{12},y_{11},y_{10},y_{9},y_{8},y_{7},y_{22},y_{21}

	// while (pend_size > 0)
	// {

	// 	std::list<unsigned int>::iterator j_it = this->get_element_in_list(index, this->_jacobsthal);

	// 	while (*j_it > 0)
	// 	{
	// 		index_order.push_back(index + *j_it);
	// 		*j_it--;
			
	// 	}

	// 	index++;
	// 	pend_size--;
	// }



	std::cout << "index_order_generator = ";
	for_each(index_order.begin(), index_order.end(), DisplayList());

	return index_order;

}

unsigned long PmergeMe::binary_sort(unsigned int n_to_insert)
{
	// std::cout << "n_to_insert = " << n_to_insert << std::endl;

	// std::cout << "S = ";
	// this->DisplayS();
	// std::cout << std::endl;

	unsigned long left = 0;
	unsigned long right = this->_S.size() -1 ;
	unsigned long mid = 0;

	if (n_to_insert < *(this->get_element_in_list(0, this->_S)))
	{
		//std::cout << "result = " << 0 <<std::endl;

		return 0;
	}

	if (n_to_insert > *(this->get_element_in_list(right, this->_S)))
	{
		//std::cout << "result = " << right <<std::endl;

		return right;
	}


	while (left < right)
	{
		mid = left + (right - left) / 2;

		if (*(this->get_element_in_list(mid, this->_S)) == n_to_insert)
		{
			break;
		}
		else if (*(this->get_element_in_list(mid, this->_S)) < n_to_insert)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}

	//std::cout << "result = " << mid <<std::endl;
	return mid;

}
