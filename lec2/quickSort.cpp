# include <iostream>
using namespace std;
// quick sort sorting algorithm
int Partition(int arr[], int s, int e)
{
    int pivot = arr[e];
    int pIndex = s;

    for(int i = s; i < e; i++)
    {
        if(arr[i] < pivot)
        {
            // swap arr[i] and arr[pIndex]
            int temp = arr[i];
            arr[i] = arr[pIndex];
            arr[pIndex] = temp;
 
            pIndex++;
        }
    }
    // swap arr[e] and arr[pIndex]
    int temp = arr[e];
    arr[e] = arr[pIndex];
    arr[pIndex] = temp;

    return pIndex;
}

void QuickSort(int arr[], int s, int e)
{
    if(s<e)
    {
    int p = Partition(arr,s, e);
    QuickSort(arr, s, (p-1));  // recursive QS call for left partition
    QuickSort(arr, (p+1), e);  // recursive QS call for right partition
    }
}

int main()
{
    int size = 0;
    cout << "Enter Size of array: "<<endl;
    cin >> size;
    int myArray[size];

    cout << "Enter " << size << " integers in any order: " << endl;
    for(int i = 0; i<size; i++)
    {
        cin >> myArray[i];
    }
    cout << "Before Sorting" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << myArray[i] << " ";
    }
    cout << endl;

    QuickSort(myArray,0,(size-1));  // quick sort called

    cout << "After Sorting" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << myArray[i] << " ";
    }

    return 0;
}