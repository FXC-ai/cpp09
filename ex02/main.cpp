#include "PmergeMe.hpp"
#include "Acess_list.hpp"

int main(int argc, char* argv[])
{

	if (argc <= 2)
	{
		std::cerr << "Error" <<std::endl;
		return 0;
	}

	std::deque<unsigned int> deq_to_sort;
	std::list<unsigned int> list_to_sort;

	argv++;
	while (argc > 1)
	{
		deq_to_sort.push_back(atoi(*argv));
		list_to_sort.push_back(atoi(*argv));

		argc--;
		argv++;
	}

	PmergeMe pmm = PmergeMe(list_to_sort, deq_to_sort);


	std::cout << "Input : ";
	pmm_deq.diplayL_deq(pmm_deq.get_deque_to_sort());
	std::cout << std::endl;



	pmm_deq.sort_deq();
	pmm_list.sort();


	std::cout << "Sorted deque = ";
	pmm_deq.diplayL_deq(pmm_deq.get_S_d());
	

	return 0;
}