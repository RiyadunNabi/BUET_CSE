#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        return majorityHelper(nums, 0, nums.size() - 1);
    }

private:
    int majorityHelper(vector<int> &nums, int left, int right)
    {
        // Base case: single element
        if (left == right)
        {
            return nums[left];
        }

        // Divide
        int mid = left + (right - left) / 2;
        int leftMajority = majorityHelper(nums, left, mid);
        int rightMajority = majorityHelper(nums, mid + 1, right);

        // Conquer: Combine results
        if (leftMajority == rightMajority)
        {
            return leftMajority;
        }

        // Count occurrences of both candidates in the current range
        int leftCount = countInRange(nums, leftMajority, left, right);
        int rightCount = countInRange(nums, rightMajority, left, right);

        // Return the one with more occurrences
        return leftCount > rightCount ? leftMajority : rightMajority;
    }

    int countInRange(vector<int> &nums, int target, int left, int right)
    {
        int count = 0;
        for (int i = left; i <= right; i++)
        {
            if (nums[i] == target)
            {
                count++;
            }
        }
        return count;
    }
};

int main()
{
    Solution solution;

    vector<int> nums1 = {3, 2, 3};
    cout << "Majority element in [3, 2, 3]: " << solution.majorityElement(nums1) << endl;

    vector<int> nums2 = {2, 2, 1, 1, 1, 2, 2};
    cout << "Majority element in [2, 2, 1, 1, 1, 2, 2]: " << solution.majorityElement(nums2) << endl;

    return 0;
}
