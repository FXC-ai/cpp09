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
		PmergeMe(std::list<unsigned int>list_to_sort, std::deque<unsigned int>deq_to_sort);
		
		std::list<unsigned int> get_list_to_sort();
		std::list<unsigned int> get_list_sorted_pairs();
		std::list<unsigned int> get_S();
		std::list<unsigned int> get_pend();

		void diplayList(std::list<unsigned int> list_to_display);

		void sort_pairs();
		void insertion_sort_pairs ();
		void binary_insertion_sort();

		void sort();


		bool check_sort(std::list<unsigned int>list_to_check);
		
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

		void sort_all();

	private :

		std::list<unsigned int> _list_to_sort;
		std::list<unsigned int> _list_sorted_pairs;

		std::list<unsigned int> _S;
		std::list<unsigned int> _pend;
		

		void switch_it(std::list<unsigned int>::iterator & it, std::list<unsigned int>::iterator & it_2);
		std::list<unsigned int>::iterator get_element_in_list(unsigned long ind, std::list<unsigned int> & list);
		std::list<unsigned int> jacobsthal_generator ();
		std::list<unsigned int> index_order_generator ();
		unsigned long binary_sort(unsigned int n_to_insert);


		std::deque<unsigned int> _deq_to_sort;
		std::deque<unsigned int> _deq_sorted_pairs;

		std::deque<unsigned int> _S_d;
		std::deque<unsigned int> _pend_d;
		

		void switch_it_deq(std::deque<unsigned int>::iterator & it, std::deque<unsigned int>::iterator & it_2);
		std::deque<unsigned int>::iterator get_element_in_deq(unsigned long ind, std::deque<unsigned int> & list);
		std::deque<unsigned int> jacobsthal_generator_deq ();
		std::deque<unsigned int> index_order_generator_deq ();
		unsigned long binary_sort_deq(unsigned int n_to_insert);
};

#endif
