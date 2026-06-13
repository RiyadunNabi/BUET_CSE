#include <iostream>
#include <vector>
using namespace std;

int minCost(vector<vector<int>>& cost, int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = cost[0][0];

    // Fill the first row
    for (int j = 1; j < n; j++) {
        dp[0][j] = dp[0][j - 1] + cost[0][j];
    }

    // Fill the first column
    for (int i = 1; i < m; i++) {
        dp[i][0] = dp[i - 1][0] + cost[i][0];
    }

    // Fill the rest of the dp table
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = cost[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
    }

    return dp[m - 1][n - 1];
}
// const int dx[]={1,0};
// const int dy[]={0,1};

// vector<vector<int>> dp;
// int minCost(vector<vector<int>> & cost,int r,int c)
// {
//     // vector<vector<int>> dp(r, vector<int>(c,0));
//     dp.resize(r,vector<int>(c,0));
//     dp[0][0]=cost[0][0];


//     for (int i = 0; i < r; i++)
//     {
//         for (int j = 0; j<c; j++)
//         {
//             if(i==0 && j==0)
//             {
//                 continue;
//             }
//             if(i==0)
//             {
//                 dp[i][j]=dp[i][j-1] +cost[i][j];
//                 continue;
//             }
//             if(j==0)
//             {
//                 dp[i][j]=dp[i-1][j]+ cost[i][j];
//                 continue;
//             }
//             dp[i][j]=cost[i][j]+min(dp[i][j-1],dp[i-1][j]);
//         }
//         // cout<<endl;
//     }
//     cout<<"The DP table:"<<endl;
//     for (int i = 0; i < r; i++)
//     {
//         for (int j = 0; j < c; j++)
//         {
//             cout<<dp[i][j]<<" ";
//         }
//         cout<<endl;
//     }
    
//     return dp[r-1][c-1];
// }


int main() {
    vector<vector<int>> cost = {
        {1, 3, 5},
        {2, 1, 2},
        {4, 3, 1}
    };
    int r = cost.size(), c= cost[0].size();
    cout << "Minimum cost path: " << minCost(cost, r, c) << endl;
    return 0;
}
