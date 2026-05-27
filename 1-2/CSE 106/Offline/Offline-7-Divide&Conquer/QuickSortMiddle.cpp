#include <iostream>
#include <vector>

using namespace std;

// Function to partition the array
int partition(vector<int> &arr, int low, int high)
{
    int mid = low + (high - low) / 2; // Middle index
    int pivot = arr[mid];             // Use the middle element as pivot
    int i = low, j = high;

    while (i <= j)
    {
        // Move i forward while elements are less than or equal to the pivot
        while (arr[i] < pivot)
        {
            i++;
        }
        // Move j backward while elements are greater than the pivot
        while (arr[j] > pivot)
        {
            j--;
        }
        // Swap elements to ensure correct placement relative to the pivot
        if (i <= j)
        {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    // Return the partition index
    return i;
}

// QuickSort function
void quickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high); // Partition index

        // Recursively sort elements before and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi, high);
    }
}

// Main function to test Quick Sort
int main()
{
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();

    cout << "Unsorted array: ";
    for (int x : arr)
    {
        cout << x << " ";
    }
    cout << endl;

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int x : arr)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
