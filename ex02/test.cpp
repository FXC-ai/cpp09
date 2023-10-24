#include <iostream>
#include <deque>

void insertion_sort(std::deque<unsigned int>& list_to_sort) 
{
    for(int i = 1; i < 5; ++i) 
    {
        unsigned int key = list_to_sort[i];
        int j = i - 1;


        while(j >= 0 && list_to_sort[j] > key) 
        {
            std::cout << "j = " << j <<std::endl;
            list_to_sort[j + 1] = list_to_sort[j];
            j--;

            for(const auto& elem : list_to_sort) 
            {
                std::cout << elem << " ";
            }
            std::cout << std::endl;

        }
        list_to_sort[j + 1] = key;
        for(const auto& elem : list_to_sort) 
        {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    std::deque<unsigned int> deq;

    deq.push_back(5);
    deq.push_back(3);
    deq.push_back(8);
    deq.push_back(4);
    deq.push_back(2);


    for(const auto& elem : deq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    insertion_sort(deq);

    // Displaying the sorted list
    std::cout << std::endl;
    std::cout << std::endl;

    for(const auto& elem : deq) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}

