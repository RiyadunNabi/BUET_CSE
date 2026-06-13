#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        vector<vector<int>> matrix(n, vector<int>(n, INT_MAX));
        for (int i = 0; i < n; i++) {
            matrix[i][i] = 0;
        }

        for (auto e : edges) {
            int u = e[0];
            int v = e[1];
            int w = e[2];
            matrix[u][v] = w;
            matrix[v][u] = w;
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX) {
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                    }
                }
            }
        }
        vector<pair<int, int>> p;
        for (int i = 0; i < n; i++) {
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] <= distanceThreshold) {
                    count++;
                }
            }
            p.push_back({count, i});
        }
        sort(p.begin(), p.end(), [](pair<int, int> &a, pair<int, int> &b) {
            if (a.first != b.first)
                return a.first < b.first;
            return a.second > b.second;
        });

        return p[0].second;
    }
};

int main() {

    return 0;
}