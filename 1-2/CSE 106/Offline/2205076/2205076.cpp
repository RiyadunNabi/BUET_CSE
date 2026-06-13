#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool isMatch(string s, string p)
{
    int sSize = s.size();
    int pSize = p.size();
    vector<vector<bool>> dp(pSize + 1, vector<bool>(sSize + 1, false));
    dp[0][0] = true;

    for (int i = 1; i <= pSize; i++)
    {
        if (p[i - 1] == '*')
        {
            dp[i][0] = dp[i - 2][0];
        }
    }

    for (int i = 1; i <= pSize; i++)
    {
        for (int j = 1; j <= sSize; j++)
        {
            if ((p[i - 1] == s[j - 1] || p[i - 1] == '.') && dp[i - 1][j - 1])
            {
                dp[i][j] = true;
            }
            else if (p[i - 1] == '*')
            {
                if (dp[i - 2][j])
                {
                    dp[i][j] = true;
                }
                else if ((p[i-2]==s[j-1] || p[i-2]=='.') && dp[i][j-1])
                {
                    dp[i][j]=true;
                }
            }
            else if(p[i-1]=='+')
            {
                if(dp[i-1][j])
                {
                    dp[i][j]=true;
                }
                else if((p[i-2]==s[j-1] || p[i-2]=='.') && dp[i][j-1])
                {
                    dp[i][j]=true;
                }
            }
        }
    }
    return dp[pSize][sSize];
}

int main()
{
    string s, p;
    cin >> s >> p;

    if (isMatch(s, p))
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }
}