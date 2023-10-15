#include <iostream>
#include <list>
#include <vector>

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


};


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

	unsigned int temp;
	it_2++;
	// FONCTIONNE PAS QUAND IL Y A UN NBR IMPAIR DE VALEURS !!!!!!
	while (it_2 != this->_list_to_sort.end())
	{	
		std::cout << "it = " << *it << " it_2 = " << *it_2 <<std::endl;
		if (*it_2 < *it)
		{	

			temp = *it;
			*it = *it_2;
			*it_2 = temp;
		}
		++it;
		++it;
		++it_2;
		++it_2;
	}	
}

void PmergeMe::insertion_sort_pairs ()
{

	// std::list<unsigned int>::interator start = this->_list_to_sort.begin();

	std::list<unsigned int>::iterator it = this->_list_to_sort.begin();
	++it;
	
	// std::list<unsigned int>::iterator it_2 = this->_list_to_sort.begin();
	// ++it_2;
	// ++it_2;
	// ++it_2;
	
	// creer un liste S avec les plus grands nombres de chaque paire.
	// analyser chaque nombre au sein de cette liste S
	// inserer les paires en conséquence dans la liste initiale


	std::list<int> S;

	for (unsigned long i = 0; i < this->_list_to_sort.size(); ++i)
	{
		if (i%2 == 1)
		{
			S.push_back(*it);
		}
		++it;
	}

	for_each(S.begin(), S.end(), DisplayList());



	// while (it_2 != this->_list_to_sort.end())
	// {
	// 	if (*it > *it_2)
	// 	{
	// 		swap_in_list(it, it_2);
	// 		it--;
	// 		it_2--;
	// 		swap_in_list(it, it_2);
	// 		it++;
	// 		it_2++;
	// 	}
	// 	it++;
	// 	it++;
	// 	it_2++;
	// 	it_2++;
	// }

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

	pmm.DisplayListToSort();
	std::cout << std::endl;

	pmm.sort_pairs();

	pmm.DisplayListToSort();


	//pmm.insertion_sort_pairs();




	return 0;
}