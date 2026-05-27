#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isMatch(string s, string p)
{
    int sSize = s.size();  // Length of the text
    int pSize = p.size();  // Length of the pattern

    // DP table to store matching results
    vector<vector<bool>> dp(pSize + 1, vector<bool>(sSize + 1, false));
    dp[0][0] = true; // Empty pattern matches empty text

    // Handle patterns starting with '*' (match zero occurrences)
    for (int i = 1; i <= pSize; i++) {
        if (p[i - 1] == '*') {
            dp[i][0] = dp[i - 2][0];
        }
    }

    // Fill the DP table
    for (int i = 1; i <= pSize; i++) {
        for (int j = 1; j <= sSize; j++) {
            if (p[i - 1] == '.' || p[i - 1] == s[j - 1]) {
                // Match current characters or '.'
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[i - 1] == '*') {
                // '*' matches zero or more occurrences
                dp[i][j] = dp[i - 2][j] || (dp[i - 1][j] && (s[j - 1] == p[i - 2] || p[i - 2] == '.'));
            } else if (p[i - 1] == '+') {
                // '+' matches one or more occurrences
                dp[i][j] = dp[i - 1][j] || (dp[i][j - 1] && (s[j - 1] == p[i - 2] || p[i - 2] == '.'));
            }
        }
    }

    return dp[pSize][sSize];
}

int main()
{
    string s, p;
    cout << "Enter text: ";
    cin >> s;
    cout << "Enter pattern: ";
    cin >> p;

    if (isMatch(s, p)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    return 0;
}
