#include <iostream>
#include <vector>
using namespace std;

bool subsetSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));
    for (int i = 0; i <= n; i++) dp[i][0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (nums[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - nums[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][target];
}

int main() {
    vector<int> nums = {1, 2, 3, 7};
    int target = 6;
    if (subsetSum(nums, target)) {
        cout << "Subset with target sum exists!" << endl;
    } else {
        cout << "No subset with target sum found!" << endl;
    }
    return 0;
}