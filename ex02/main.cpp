#include "PmergeMe.hpp"

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

	pmm.sort_all();




	return 0;
}