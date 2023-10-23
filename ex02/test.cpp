#include <iostream>
#include <list>


std::list<unsigned int>::iterator get_element_in_list(unsigned long ind, std::list<unsigned int> & list)
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

unsigned long binary_sort(unsigned int n_to_insert, std::list<unsigned int> & S)
{
    unsigned long left = 0;
    unsigned long right = S.size();
    unsigned long mid = 0;

    while (left < right)
    {
        mid = left + (right - left) / 2;

        if (*(get_element_in_list(mid, S)) < n_to_insert)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }

    return left;

}

int main() {
    std::list<unsigned int> S;

	S.push_back(1);
	S.push_back(85);
	S.push_back(90);
	S.push_back(99);
	S.push_back(100);
	S.push_back(101);


//1 85 90 99 100 101


    int valueToInsert = 3;
    
    int position = binary_sort(valueToInsert, S);

    std::cout << "Value " << valueToInsert << " should be inserted at index " << position << std::endl;



    return 0;
}
