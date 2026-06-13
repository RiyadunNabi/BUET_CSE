#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Edge {
    int to, rev, cap;
};

int V;
vector<vector<Edge>> adj;

// Add edge to graph (u->v with capacity c)
void addEdge(int u, int v, int c) {
    adj[u].push_back({v, (int)adj[v].size(), c});
    adj[v].push_back({u, (int)adj[u].size() - 1, 0}); // reverse edge with 0 capacity
}

// Standard DFS to find augmenting path
int dfs(int u, int t, int flow, vector<bool> &visited) {
    if (u == t) return flow;
    visited[u] = true;
    for (auto &e : adj[u]) {
        if (!visited[e.to] && e.cap > 0) {
            int pushed = dfs(e.to, t, min(flow, e.cap), visited);
            if (pushed > 0) {
                e.cap -= pushed;
                adj[e.to][e.rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

// Ford-Fulkerson main function
int fordFulkerson(int s, int t) {
    int maxFlow = 0;
    while (true) {
        vector<bool> visited(V, false);
        int flow = dfs(s, t, INT_MAX, visited);
        if (flow == 0) break;
        maxFlow += flow;
    }
    return maxFlow;
}

int main() {
    V = 6;
    adj.assign(V, vector<Edge>());

    // Example graph (same as before)
    addEdge(0, 1, 16);
    addEdge(0, 2, 13);
    addEdge(1, 2, 10);
    addEdge(2, 1, 4);
    addEdge(1, 3, 12);
    addEdge(3, 2, 9);
    addEdge(2, 4, 14);
    addEdge(4, 3, 7);
    addEdge(3, 5, 20);
    addEdge(4, 5, 4);

    cout << "The maximum possible flow is " << fordFulkerson(0, 5) << endl;
    return 0;
}

//we can turn the list into matrix and use endmonds-karp
/*
vector<tuple<int, int, int>> edges = {
    {0, 1, 16}, {0, 2, 13}, {1, 2, 10}, {1, 3, 12}, {2, 1, 4},
    {2, 4, 14}, {3, 2, 9}, {3, 5, 20}, {4, 3, 7}, {4, 5, 4}
};

for (auto &e : edges) {
    int u, v, c;
    tie(u, v, c) = e;
    graph[u][v] = c; // or += if you can have multi-edges
}
*/

/*
BFS-based Ford-Fulkerson (Edmonds-Karp) with Adjacency List
Here’s a clean, function-based example—very similar in style to the ones above, but using BFS and a parent array:

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct Edge {
    int to, rev, cap;
};

int V;
vector<vector<Edge>> adj;

void addEdge(int u, int v, int c) {
    adj[u].push_back({v, (int)adj[v].size(), c});
    adj[v].push_back({u, (int)adj[u].size() - 1, 0});
}

bool bfs(int s, int t, vector<int> &parent, vector<int> &parentEdge) {
    queue<int> q;
    vector<bool> visited(V, false);
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i = 0; i < adj[u].size(); ++i) {
            Edge &e = adj[u][i];
            if (!visited[e.to] && e.cap > 0) {
                visited[e.to] = true;
                parent[e.to] = u;
                parentEdge[e.to] = i;
                if (e.to == t)
                    return true;
                q.push(e.to);
            }
        }
    }
    return false;
}

int edmondsKarp(int s, int t) {
    int maxFlow = 0;
    vector<int> parent(V), parentEdge(V);
    while (bfs(s, t, parent, parentEdge)) {
        // Find bottleneck
        int flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            Edge &e = adj[u][parentEdge[v]];
            flow = min(flow, e.cap);
        }
        // Update capacities
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            Edge &e = adj[u][parentEdge[v]];
            e.cap -= flow;
            adj[e.to][e.rev].cap += flow;
        }
        maxFlow += flow;
    }
    return maxFlow;
}

int main() {
    V = 6;
    adj.assign(V, vector<Edge>());
    // Sample graph (same as before)
    addEdge(0, 1, 16);
    addEdge(0, 2, 13);
    addEdge(1, 2, 10);
    addEdge(2, 1, 4);
    addEdge(1, 3, 12);
    addEdge(3, 2, 9);
    addEdge(2, 4, 14);
    addEdge(4, 3, 7);
    addEdge(3, 5, 20);
    addEdge(4, 5, 4);

    cout << "The maximum possible flow is " << edmondsKarp(0, 5) << endl;
    return 0;
}

*/
