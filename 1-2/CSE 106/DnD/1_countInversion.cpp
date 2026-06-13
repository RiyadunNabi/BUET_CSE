#include <iostream>
using namespace std;

// Function to merge two halves and count inversions
int mergeAndCount(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    int inv_count = 0;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);  // Count inversions
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inv_count;
}

// Function to count inversions using merge sort
int countInversions(int arr[], int temp[], int left, int right) {
    int inv_count = 0;
    if (left < right) {
        int mid = (left + right) / 2;

        inv_count += countInversions(arr, temp, left, mid);
        inv_count += countInversions(arr, temp, mid + 1, right);
        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

// Wrapper function
int getInversionCount(int arr[], int n) {
    int temp[n];
    return countInversions(arr, temp, 0, n - 1);
}

// Main function with predefined array
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};  // Reverse sorted
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << getInversionCount(arr, n) << "\n";  // Expected output: 45
    return 0;
}
