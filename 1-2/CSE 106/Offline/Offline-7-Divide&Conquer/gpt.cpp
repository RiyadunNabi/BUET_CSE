#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

struct Result {
    int maxSum;
    int start;
    int end;
    int length;
};

Result findCrossingStreak(const vector<int>& scores, int left, int mid, int right) {
    int leftSum = INT_MIN, rightSum = INT_MIN;
    int sum = 0, leftIdx = mid, rightIdx = mid + 1;

    // Find the maximum sum on the left half
    for (int i = mid; i >= left; i--) {
        sum += scores[i];
        if (sum > leftSum) {
            leftSum = sum;
            leftIdx = i;
        }
    }

    sum = 0;
    // Find the maximum sum on the right half
    for (int i = mid + 1; i <= right; i++) {
        sum += scores[i];
        if (sum > rightSum) {
            rightSum = sum;
            rightIdx = i;
        }
    }

    return {leftSum + rightSum, leftIdx, rightIdx, rightIdx - leftIdx + 1};
}

Result findHottestStreak(const vector<int>& scores, int left, int right) {
    // Base case: Single element
    if (left == right) {
        return {scores[left], left, left, 1};
    }

    int mid = left + (right - left) / 2;

    // Recursively find streaks in left and right halves
    Result leftResult = findHottestStreak(scores, left, mid);
    Result rightResult = findHottestStreak(scores, mid + 1, right);

    // Find crossing streak
    Result crossResult = findCrossingStreak(scores, left, mid, right);

    // Compare results
    Result bestResult = leftResult;

    if (rightResult.maxSum > bestResult.maxSum || 
        (rightResult.maxSum == bestResult.maxSum && rightResult.length < bestResult.length)) {
        bestResult = rightResult;
    }

    if (crossResult.maxSum > bestResult.maxSum || 
        (crossResult.maxSum == bestResult.maxSum && crossResult.length < bestResult.length)) {
        bestResult = crossResult;
    }

    return bestResult;
}

int main() {
    vector<int> scores = {6, 3, -7, 3, -2, 5, -1, 4, -3, 2};

    Result result = findHottestStreak(scores, 0, scores.size() - 1);

    cout << "Hottest streak: [";
    for (int i = result.start; i <= result.end; i++) {
        cout << scores[i];
        if (i != result.end) cout << ", ";
    }
    cout << "] with a sum of " << result.maxSum << endl;

    return 0;
}
