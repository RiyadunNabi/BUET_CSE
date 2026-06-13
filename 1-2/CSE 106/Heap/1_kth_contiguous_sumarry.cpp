/*To find the K-th largest sum of a contiguous subarray, we can use a Min-Heap (Priority Queue) approach efficiently.*/
//Efficient Approach: Min-Heap (O(N² log K))
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int findKthLargestSubarraySum(vector<int>& nums, int K) {
    priority_queue<int, vector<int>, greater<int>> minHeap; // Min-Heap

    int n = nums.size();
    
    // Generate all subarrays and store their sums
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];  // Compute subarray sum

            if (minHeap.size() < K) {
                minHeap.push(sum);
            } else if (sum > minHeap.top()) {
                minHeap.pop();  // Remove smallest
                minHeap.push(sum);
            }
        }
    }

    return minHeap.top();  // K-th largest sum
}

int main() {
    vector<int> nums = {10, -10, 20, -40, 30}; 
    int K = 3;  
    cout << "K-th Largest Subarray Sum: " << findKthLargestSubarraySum(nums, K) << endl;
    return 0;
}

 
/*  Alternative Approach: Sorting All Sums (O(N² log N²))
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findKthLargestSubarraySumSort(vector<int>& nums, int K) {
    vector<int> sums;
    int n = nums.size();

    // Compute all subarray sums
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += nums[j];
            sums.push_back(sum);
        }
    }

    sort(sums.rbegin(), sums.rend()); // Sort in descending order
    return sums[K - 1]; // K-th largest sum
}

int main() {
    vector<int> nums = {10, -10, 20, -40, 30};
    int K = 3;
    cout << "K-th Largest Subarray Sum: " << findKthLargestSubarraySumSort(nums, K) << endl;
    return 0;
}

*/