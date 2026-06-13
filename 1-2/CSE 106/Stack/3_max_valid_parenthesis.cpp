#include <iostream>
using namespace std;

int longestValidParenthesesOptimized(string s) {
    int maxLength = 0, open = 0, close = 0;
    
    // Left to right scan
    for (char c : s) {
        if (c == '(') open++;
        else close++;
        if (open == close) maxLength = max(maxLength, 2 * close);
        if (close > open) open = close = 0; // Reset if invalid
    }

    open = close = 0;  // Reset counters

    // Right to left scan
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == ')') close++;
        else open++;
        if (open == close) maxLength = max(maxLength, 2 * open);
        if (open > close) open = close = 0; // Reset if invalid
    }

    return maxLength;
}

int main() {
    string s = "(()))())(";
    cout << "Longest Valid Parentheses Length: " << longestValidParenthesesOptimized(s) << endl;
    return 0;
}



/*   //DP

#include <iostream>
#include <vector>
using namespace std;

int longestValidParenthesesDP(string s) {
    int n = s.length(), maxLength = 0;
    vector<int> dp(n, 0);

    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            if (s[i-1] == '(') {
                dp[i] = (i >= 2 ? dp[i-2] : 0) + 2;
            } else if (i - dp[i-1] > 0 && s[i - dp[i-1] - 1] == '(') {
                dp[i] = dp[i-1] + ((i - dp[i-1]) >= 2 ? dp[i - dp[i-1] - 2] : 0) + 2;
            }
            maxLength = max(maxLength, dp[i]);
        }
    }

    return maxLength;
}

int main() {
    string s = "(()))())(";
    cout << "Longest Valid Parentheses Length: " << longestValidParenthesesDP(s) << endl;
    return 0;
}

*/