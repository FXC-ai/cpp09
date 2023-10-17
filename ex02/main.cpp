#include <iostream>
#include <list>
#include <vector>
#include "Acess_list.hpp"

class DisplayList
{
	public :
		void operator()(unsigned int a)
		{
			std::cout << a << " ";
		}
};


template <typename T>
void display(T & a)
{
	std::cout << a << " ";
}

void swap_in_list(std::list<unsigned int>::iterator & it, std::list<unsigned int>::iterator & it_2)
{
	unsigned int temp;

	temp = *it;
	*it = *it_2;
	*it_2 = temp;
};

class PmergeMe
{
	public :
		PmergeMe(std::list<unsigned int>list_to_sort);
		std::list<unsigned int> get_list_to_sort();
		void DisplayListToSort();

		void sort_pairs();
		void insertion_sort_pairs ();

	private :
		std::list<unsigned int>_list_to_sort;
		void switch_it(std::list<unsigned int>::iterator & it, std::list<unsigned int>::iterator & it_2);
		std::list<unsigned int>::iterator get_element_in_list(unsigned long ind, std::list<unsigned int> & list);

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


PmergeMe::PmergeMe(std::list<unsigned int>list_to_sort) : _list_to_sort(list_to_sort){};

std::list<unsigned int> PmergeMe::get_list_to_sort()
{
	return this->_list_to_sort;
}

void PmergeMe::DisplayListToSort()
{
	for_each(this->_list_to_sort.begin(), this->_list_to_sort.end(), DisplayList());
}

void PmergeMe::sort_pairs()
{
	std::list<unsigned int>::iterator it = this->_list_to_sort.begin();
	std::list<unsigned int>::iterator it_2 = this->_list_to_sort.begin();

	unsigned long loop_count = this->_list_to_sort.size() / 2;

	//unsigned int temp;
	it_2++;
	// FONCTIONNE PAS QUAND IL Y A UN NBR IMPAIR DE VALEURS !!!!!!

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
	std::cout << "After sorting pairs :" << std::endl;
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
	std::cout << std::endl;
	std::cout << std::endl;
}

void PmergeMe::insertion_sort_pairs ()
{
	// std::list<unsigned int>::interator start = this->_list_to_sort.begin();

	std::list<unsigned int>::iterator it = this->_list_to_sort.begin();
	

	// creer un liste S avec les plus grands nombres de chaque paire.
	// analyser chaque nombre au sein de cette liste S
	// inserer les paires en conséquence dans la liste initiale


	std::list<unsigned int> S;

	for (unsigned long i = 0; i < this->_list_to_sort.size(); ++i)
	{
		if (i%2 == 1)
		{
			S.push_back(*it);
		}
		++it;
	}


	for (unsigned long index = 1;index < S.size(); ++index)
	{
		std::cout << std::endl;
		for_each(S.begin(), S.end(), DisplayList());
		std::cout << std::endl;

		std::list<unsigned int>::iterator start = S.begin();
		std::list<unsigned int>::iterator it_current = this->get_element_in_list(index, S);
		std::list<unsigned int>::iterator it_mover = this->get_element_in_list(index - 1, S);
		unsigned long ind_to_insert = 0;

		std::cout << "Ici on compare le current " << *it_current << " avec le mover " << *it_mover <<std::endl;
		while (*it_current < *it_mover)
		{
			ind_to_insert++;

			if (it_mover != start)
			{
				--it_mover;
			}
			else
			{
				break;
			}
		}
	

		std::cout << "il faut reculer " << *it_current << " de " << ind_to_insert << " places." << " cad avant "<< *it_mover <<std::endl;


		// std::cout << index << " : " << " current value = " << *it_current << std::endl;

		// unsigned int temp_value;
		// temp_value = *it_current;
		// --it_current;

		// unsigned long ind_to_insert = 0;

		// std::cout << "Ici on compare " << temp_value << " avec " << *it_current <<std::endl;
		// while (temp_value < *it_current && it_current != start)
		// {
		// 	ind_to_insert++;
		// 	--it_current;
		// }

		// std::list<unsigned int>::iterator it_to_insert = this->get_element_in_list(index - ind_to_insert, S);
		
		// std::cout << "il faut reculer " << temp_value << " de " << ind_to_insert << " places." << " cad avant "<< *it_to_insert <<std::endl;

		// if (ind_to_insert != 0)
		// {
		// 	//break;
		// 	//it_to_insert--;
		// 	if (it_to_insert == start)
		// 	{
		// 		S.erase(this->get_element_in_list(index, S));
		// 		S.push_front(temp_value);
		// 	}
		// 	else
		// 	{
		// 		S.erase(this->get_element_in_list(index, S));
		// 		S.insert(it_to_insert, temp_value);
		// 	}

		// 	//S.insert(it_to_insert, temp_value);
		// 	std::cout << std::endl;
		// 	for_each(S.begin(), S.end(), DisplayList());
		// 	std::cout << std::endl;

		// }
		// while (start != it_current)
		// {
		// 	--it_current;

		// 	std::cout << "Analyse de " << temp_value << " et " << *it_current << " : " << std::endl;
		// 	if (temp_value > *it_current)
		// 	{
		// 		std::cout << "index = " << index << std::endl;
		// 		std::cout << "ind_to_insert = " << ind_to_insert << std::endl;

		// 		std::list<unsigned int>::iterator it_to_insert = this->get_element_in_list((index - ind_to_insert -1), S);

		// 		std::cout << "Je veux switch " << *it_to_insert << " " << *it_current <<std::endl;
		// 		std::cout << std::endl;


		// 		break;
		// 	}
		// 	else
		// 	{
		// 		std::cout << "La faut insert..." <<std::endl;
		// 		ind_to_insert++;
		// 	}
		// }
	}


	std::cout << std::endl;
	for_each(S.begin(), S.end(), DisplayList());
	std::cout << std::endl;


	//DEBUG
	int d = 0;
	std::cout << std::endl;
	std::cout << "After insertion_sort_pairs :" << std::endl;
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
	std::cout << std::endl;

}


int main(int argc, char* argv[])
{

	if (argc <= 1)
	{
		std::cerr << "Error" <<std::endl;
		return 0;
	}

	std::list<unsigned int> list_to_sort;

	argv++;
	while (argc > 1)
	{
		// std::cout << *argv << std::endl;
		//we will need some parsing here

		list_to_sort.push_back(atoi(*argv));

		argc--;
		argv++;
	}

	//list_to_sort.insert(++list_to_sort.begin(), 42);


	//std::for_each(list_to_sort.begin(), list_to_sort.end(), DisplayList());

	PmergeMe pmm = PmergeMe(list_to_sort);

	std::cout << "Input : ";
	pmm.DisplayListToSort();
	std::cout << std::endl;
	std::cout << std::endl;

	pmm.sort_pairs();
	pmm.insertion_sort_pairs();

	std::cout << std::endl;
	pmm.DisplayListToSort();


	//pmm.insertion_sort_pairs();




	return 0;
}