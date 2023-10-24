#include "PmergeMe.hpp"
#include "Acess_list.hpp"

int main(int argc, char* argv[])
{

	if (argc <= 2)
	{
		std::cerr << "Error" <<std::endl;
		return 0;
	}

	std::list<unsigned int> list_to_sort;

	argv++;
	while (argc > 1)
	{
		list_to_sort.push_back(atoi(*argv));

		argc--;
		argv++;
	}

	PmergeMe pmm = PmergeMe(list_to_sort);

	std::cout << "Input : ";
	pmm.diplayList(pmm.get_list_to_sort());
	std::cout << std::endl;

	// pmm.sort_pairs();

	// pmm.insertion_sort_pairs();

	//pmm.jacobsthal_generator();

	// pmm.binary_insertion_sort();

	pmm.sort();


	std::cout << "Sorted list = ";
	pmm.diplayList(pmm.get_S());
	

	return 0;
}