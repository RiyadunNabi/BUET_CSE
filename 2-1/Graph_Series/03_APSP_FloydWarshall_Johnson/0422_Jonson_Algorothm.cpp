#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
};

void bellmanFord(int src, int V, vector<Edge>& edges, vector<int>& dist) {
    dist[src] = 0;
    for (int i = 1; i <= V - 1; i++) {
        for (auto edge : edges) {
            if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    // Optional: detect negative weight cycles
    for (auto edge : edges) {
        if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
            cout << "Graph contains a negative weight cycle.\n";
            exit(0);
        }
    }
}

void dijkstra(int src, int V, vector<pair<int, int>> adj[], vector<int>& dist) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

void johnsonAlgorithm(int V, vector<Edge>& edges) {
    vector<Edge> modifiedEdges = edges;
    for (int i = 0; i < V; i++) {
        modifiedEdges.push_back({V, i, 0}); // connect dummy node to all
    }

    vector<int> h(V + 1, INT_MAX);
    bellmanFord(V, V + 1, modifiedEdges, h); // V is dummy node

    vector<pair<int, int>> adj[V];
    for (auto edge : edges) {
        int newWeight = edge.weight + h[edge.u] - h[edge.v];
        adj[edge.u].push_back({edge.v, newWeight});
    }

    for (int i = 0; i < V; i++) {
        vector<int> dist(V, INT_MAX);
        dijkstra(i, V, adj, dist);

        cout << "Shortest distances from node " << i << ":\n";
        for (int j = 0; j < V; j++) {
            if (dist[j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << dist[j] - h[i] + h[j] << " ";
            }
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<Edge> edges(E);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    johnsonAlgorithm(V, edges);

    return 0;
}