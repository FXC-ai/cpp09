#include "PmergeMe.hpp"
#include "Acess_list.hpp"

int main(int argc, char* argv[])
{

	if (argc <= 2)
	{
		std::cerr << "Error" <<std::endl;
		return 0;
	}

	std::deque<unsigned int> list_to_sort;

	argv++;
	while (argc > 1)
	{
		list_to_sort.push_back(atoi(*argv));

		argc--;
		argv++;
	}

	PmergeMe pmm = PmergeMe(list_to_sort);

	std::cout << "Input : ";
	pmm.diplayL_deq(pmm.get_deque_to_sort());
	std::cout << std::endl;



	pmm.sort_deq();


	std::cout << "Sorted list = ";
	pmm.diplayL_deq(pmm.get_S_d());
	

	return 0;
}