#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isMatch(string t, string p) {
    int n = t.size();
    int m = p.size();
    vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

    // Base case: empty text and empty pattern
    dp[0][0] = true;

    // Handle patterns with '*' or '+' at the beginning
    for (int j = 1; j <= m; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2]; // '*' can match zero occurrences
        }
    }

    // Fill the DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '.' || p[j - 1] == t[i - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 2] || (dp[i - 1][j] && (t[i - 1] == p[j - 2] || p[j - 2] == '.'));
            } else if (p[j - 1] == '+') {
                dp[i][j] =dp[i][j-1] || dp[i - 1][j] && (t[i - 1] == p[j - 2] || p[j - 2] == '.');
            }
        }
    }

    return dp[n][m];
}

int main() {
    string t, p;
    cin >> t >> p;

    if (isMatch(t, p)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    return 0;
}
