#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>


class PmergeMe
{
	public :
		PmergeMe(std::list<unsigned int>list_to_sort);
		std::list<unsigned int> get_list_to_sort();
		std::list<unsigned int> get_list_sorted_pairs();
		std::list<unsigned int> get_jacobsthal();
		std::list<unsigned int> get_S();
		std::list<unsigned int> get_pend();

		void diplayList(std::list<unsigned int> list_to_display);

		void sort_pairs();
		void insertion_sort_pairs ();
		std::list<unsigned int> index_order_generator ();

		void insertion_sort();

		bool check_sort(std::list<unsigned int>list_to_check);


	private :
		std::list<unsigned int> _list_to_sort;
		std::list<unsigned int> _list_sorted_pairs;

		std::list<unsigned int> _S;
		std::list<unsigned int> _pend;
		
		std::list<unsigned int> _jacobsthal;

		void switch_it(std::list<unsigned int>::iterator & it, std::list<unsigned int>::iterator & it_2);
		std::list<unsigned int>::iterator get_element_in_list(unsigned long ind, std::list<unsigned int> & list);
		void jacobsthal_generator ();
		unsigned long binary_sort(unsigned int n_to_insert);
};

#endif
