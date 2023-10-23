#include "PmergeMe.hpp"
#include "Acess_list.hpp"

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
		list_to_sort.push_back(atoi(*argv));

		argc--;
		argv++;
	}

	if (list_to_sort.size() < 3)
	{
		std::cout << "Error" <<std::endl;
		return 0;
	}

	PmergeMe pmm = PmergeMe(list_to_sort);

	std::cout << "Input : ";
	pmm.diplayList(pmm.get_list_to_sort());
	std::cout << std::endl;

	pmm.sort_pairs();

	pmm.insertion_sort_pairs();

	//pmm.jacobsthal_generator();

	pmm.insertion_sort();

	pmm.diplayList(pmm.get_S());
	std::cout << std::endl;

	return 0;
}