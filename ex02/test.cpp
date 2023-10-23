#include <iostream>
#include <vector>

int findInsertPosition(const std::vector<int>& vec, int value) {
    int left = 0;
    int right = vec.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (vec[mid] == value) {
            return mid; // Value found, return the current index
        }
        else if (vec[mid] < value) {
            left = mid + 1; // Search in the right half
        }
        else {
            right = mid - 1; // Search in the left half
        }
    }

    return left; // Return the index where the value should be inserted
}

int main() {
    std::vector<int> myVector;

	myVector.push_back(1);
	myVector.push_back(3);
	myVector.push_back(5);
	myVector.push_back(7);
	myVector.push_back(9);
	myVector.push_back(11);
	myVector.push_back(13);
	myVector.push_back(15);
	myVector.push_back(17);
	myVector.push_back(19);


    int valueToInsert = 8;
    
    int position = findInsertPosition(myVector, valueToInsert);

    std::cout << "Value " << valueToInsert << " should be inserted at index " << position << std::endl;

    return 0;
}
