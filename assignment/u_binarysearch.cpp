#include <iostream>

using namespace std;

// Binary search function for integer arrays
int BinarySearch(int A[], int size, int key) 
{
    int left = 0;
    int right = size - 1;

    while (left <= right) 
	{
        int mid = left + (right - left) / 2;

        if (A[mid] == key)
            return mid;
        else if (A[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    // If the key is not found, return -1
    return -1;
}

int main() 
{
    int numbers[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int key = 7;
    int size = sizeof(numbers) / sizeof(numbers[0]);
    int index = BinarySearch(numbers, size, key);
    
    if (index != -1) 
	{
        cout << "Key found at index: " << index << endl;
    } 
	else 
	{
        cout << "Key not found" << endl;
    }

    return 0;
}

