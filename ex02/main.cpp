#include "PmergeMe.hpp"
#include "Acess_list.hpp"

// template <typename T>
// void display(T & a)
// {
// 	std::cout << a << " ";
// }


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
	std::cout << std::endl;
	std::cout << std::endl;

	pmm.insertion_sort_pairs();
	std::cout << std::endl;
	std::cout << std::endl;



	pmm.jacobsthal_generator();
	std::cout << std::endl;
	std::cout << std::endl;



	pmm.index_order_generator();
	std::cout << std::endl;
	std::cout << std::endl;

	// pmm.binary_sort(8);
	// std::cout << "-------------" <<std::endl;	

	// //pmm.binary_sort(198);
	// pmm.binary_sort(12);
	// std::cout << "-------------" <<std::endl;	

	// pmm.binary_sort(23);
	// std::cout << "-------------" <<std::endl;	

	// pmm.binary_sort(34);
	// std::cout << "-------------" <<std::endl;	

	// pmm.binary_sort(45);
	// std::cout << "-------------" <<std::endl;	


	// pmm.binary_sort(56);
	// std::cout << "-------------" <<std::endl;	

	// pmm.binary_sort(87);
	// std::cout << "-------------" <<std::endl;	

	// pmm.binary_sort(870);
	// std::cout << "-------------" <<std::endl;	


	//pmm.binary_sort(108);
	//pmm.binary_sort(176);
	//pmm.binary_sort(8);
	std::cout << std::endl;


	//pmm.insertion_sort_pairs();

	//for_each(pmm.get_jacobsthal().begin(), pmm.get_jacobsthal().end(), DisplayList());
	//std::cout << " SIZE = "<< pmm.get_jacobsthal().size() << std::endl;
	//std::cout << " o = "<< *(pmm.get_jacobsthal().begin()) << std::endl;

	return 0;
}