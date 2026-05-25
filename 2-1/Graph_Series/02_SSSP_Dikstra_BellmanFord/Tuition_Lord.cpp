#include <bits/stdc++.h>
using namespace std;

int main() {
    int K, N, X;
    cin >> K >> N >> X;
    
    vector<vector<tuple<int, int, int>>> graph(N + 1); // {neighbor, travel time, travel cost}
    
    for (int i = 0; i < X; ++i) {
        int u, v, t, c;
        cin >> u >> v >> t >> c;
        graph[u].push_back({v, t, c});
        graph[v].push_back({u, t, c});
    }
    
    int S, D;
    cin >> S >> D;
    
    // priority_queue: (total cost, total time, current node, path, transfers)
    priority_queue<tuple<int, int, int, vector<int>, int>, 
                   vector<tuple<int, int, int, vector<int>, int>>, 
                   greater<tuple<int, int, int, vector<int>, int>>> pq;
    
    pq.push({0, 0, S, {S}, 0});
    
    vector<int> visited(N + 1, INT_MAX);
    
    while (!pq.empty()) {
        auto [totalCost, totalTime, u, path, transfers] = pq.top();
        pq.pop();
        
        if (u == D) {
            for (int i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i != path.size() - 1) cout << "->";
            }
            cout << " " << totalTime << " " << totalCost << endl;
            return 0;
        }
        
        if (visited[u] <= totalCost) continue;
        visited[u] = totalCost;
        
        for (auto &[v, t, c] : graph[u]) {
            int newTime = totalTime + t;
            if (transfers >= 1) newTime += 1; // wait 1 hour for transfer (after starting)
            int opportunityCost = (newTime - totalTime) * K;
            int newCost = totalCost + c + opportunityCost;
            
            vector<int> newPath = path;
            newPath.push_back(v);
            
            pq.push({newCost, newTime, v, newPath, transfers + 1});
        }
    }
    
    cout << "Error" << endl;
    return 0;
}
