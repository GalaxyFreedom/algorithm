#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <time.h>


using namespace std;
using namespace std::chrono;

void randomArray(int arr[], int length, int upperBound, int lowerBound) {
    srand(time(NULL));
    for (int i = 0; i < length; i++) {
        arr[i] = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
    }
}

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
        // insert the key at the missing position
        arr[j + 1] = key;
    }
}

void merge(int arr[], int l, int m, int r, int size)
{
    int i = l;
    int j = m + 1;
    int k = l;

    /* create temp array */
    int temp[size];

    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
            k++;
        }
        else {
            temp[k] = arr[j];
            j++;
            k++;
        }
    }
    /* Copy the remaining elements of first half, if there are any */
    while (i <= m) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of second half, if there are any */
    while (j <= r) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    /* Copy the temp array to original array */
    for (int p = l; p <= r; p++) {
        arr[p] = temp[p];
    }
}

/* l is for left index and r is
right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r, int size)
{
    if (l < r) {
        // find midpoint
        int m = (l + r) / 2;

        /* recursive mergesort first
        and second halves */
        mergeSort(arr, l, m, size);
        mergeSort(arr, m + 1, r, size);

        // merge
        merge(arr, l, m, r, size);
    }
}


void quickSort() {

}

void printArray(int arr[], int length) {
    cout <<"Array: " << endl;
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main() {
    cout << "Enter size of array: " << endl;
    int size;
    cin >> size;
    int myArray[size];

    cout << "Enter " << size << " integers in any order: " << endl;
    for (int i = 0; i < size; i++) {
        cin >> myArray[i];
    }
    cout << "Before Sorting" << endl;
    for (int i = 0; i < size; i++) {
        cout << myArray[i] << " ";
    }
    cout << endl;
    mergeSort(myArray, 0, (size - 1), size); // mergesort(arr,left,right) called

    cout << "After Sorting" << endl;
    for (int i = 0; i < size; i++) {
        cout << myArray[i] << " ";
    }

    return 0;

}