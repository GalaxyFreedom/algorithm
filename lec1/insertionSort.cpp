#include <iostream>
#include <vector>
using namespace std;
/*
procedure insertionSort(A: list of sortable items)
   n = length(A)
   for i = 1 to n - 1 do
       j = i
       while j > 0 and A[j-1] > A[j] do
           swap(A[j], A[j-1])
           j = j - 1
       end while
   end for
end procedure
*/
// Function to sort an array using
// insertion sort
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void recursiveInsertionSort(vector<int>& arr, int n)
{
    // Base case: if the array has only one element, it is already sorted
    if (n <= 1) {
        return;
    }

    // Sort the first n-1 elements of the array recursively
    recursiveInsertionSort(arr, n - 1);

    // Insert the nth element into its correct position in the sorted subarray
    int last = arr[n - 1];
    int j = n - 2;

    // Shift elements to the right to make space for the nth element
    while (j >= 0 && arr[j] > last)
    {
        arr[j + 1] = arr[j];
        j--;
    }

    // Place the nth element in its correct position
    arr[j + 1] = last;
}

void printArray(vector<int>& arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    vector<int> arr = {12, 11, 13, 5, 6};
    int n = arr.size();

    recursiveInsertionSort(arr, n);
    printArray(arr, n);

    return 0;
}