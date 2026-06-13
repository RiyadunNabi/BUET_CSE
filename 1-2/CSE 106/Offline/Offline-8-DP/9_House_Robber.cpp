#include <iostream>
#include <vector>
using namespace std;

int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];

    int prev2 = 0, prev1 = nums[0];
    for (int i = 1; i < nums.size(); i++) {
        int current = max(prev1, prev2 + nums[i]);
        prev2 = prev1;
        prev1 = current;
    }
    return prev1;
}

int main() {
    vector<int> nums = {2, 7, 9, 3, 1};
    cout << "Maximum amount robbed: " << rob(nums) << endl;
    return 0;
}
