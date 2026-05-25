#include <bits/stdc++.h>
using namespace std;

typedef pair<long long, int> pli;

int main() {
    int n, m, f;
    cin >> n >> m >> f;
    
    vector<int> capacity(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> capacity[i];
    }

    vector<vector<pli>> adj(n + 1); // adj list: (neighbor, weight)
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    int k;
    cin >> k;

    // Dijkstra from lab 1
    vector<long long> dist(n + 1, 1e18);
    priority_queue<pli, vector<pli>, greater<pli>> pq;
    
    dist[1] = 0;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto [w, v] : adj[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    // Build a list of labs sorted by total cost (walking cost + entry fee)
    vector<pair<long long, int>> labs;
    for (int i = 1; i <= n; ++i) {
        labs.push_back({dist[i] + f, i});
    }
    sort(labs.begin(), labs.end());

    vector<int> result;
    for (int i = 0; i < k; ++i) {
        bool assigned = false;
        for (auto &[cost, lab] : labs) {
            if (capacity[lab] > 0) {
                result.push_back(cost);
                capacity[lab]--;
                assigned = true;
                break;
            }
        }
        if (!assigned) {
            result.push_back(-1);
        }
    }

    for (int x : result) cout << x << " ";
    cout << endl;

    return 0;
}
