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
		std::list<unsigned int> get_jacobsthal();
		void DisplayListToSort();
		void DisplayJacobsthal();
		void DisplayS();
		void DisplayPend();


		void sort_pairs();
		void insertion_sort_pairs ();


		void jacobsthal_generator ();
		std::list<unsigned int> index_order_generator ();
		unsigned long binary_sort(unsigned int n_to_insert);


	private :
		std::list<unsigned int> _list_to_sort;
		std::list<unsigned int> _list_sorted_pairs;
		std::list<unsigned int> _S;
		std::list<unsigned int> _pend;
		std::list<unsigned int> _jacobsthal;

		void switch_it(std::list<unsigned int>::iterator & it, std::list<unsigned int>::iterator & it_2);
		std::list<unsigned int>::iterator get_element_in_list(unsigned long ind, std::list<unsigned int> & list);
};

#endif
