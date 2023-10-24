#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <list>
#include <vector>
#include <deque>

class DisplayList;


class PmergeMe
{
	public :
		PmergeMe(std::deque<unsigned int>list_to_sort);
		std::deque<unsigned int> get_deque_to_sort();
		std::deque<unsigned int> get_deque_sorted_pairs();
		std::deque<unsigned int> get_S_d();
		std::deque<unsigned int> get_pend_d();

		void diplayL_deq(std::deque<unsigned int> list_to_display);

		void sort_pairs_deq();
		void insertion_sort_pairs_deq ();
		void binary_insertion_sort_deq();

		void sort_deq();


		bool check_sort_deq(std::deque<unsigned int>list_to_check);


	private :
		std::deque<unsigned int> _deq_to_sort;
		std::deque<unsigned int> _deq_sorted_pairs;

		std::deque<unsigned int> _S_d;
		std::deque<unsigned int> _pend_d;
		

		void switch_it_deq(std::deque<unsigned int>::iterator & it, std::deque<unsigned int>::iterator & it_2);
		std::deque<unsigned int>::iterator get_element_in_deq(unsigned long ind, std::deque<unsigned int> & list);
		std::deque<unsigned int> jacobsthal_generator_deq ();
		std::deque<unsigned int> index_order_generator_deq ();
		unsigned long binary_sort(unsigned int n_to_insert);
};

#endif
