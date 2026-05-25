#include <iostream>
#include <vector>
using namespace std;

void bellmanFord(int V, int E, vector<int>& u, vector<int>& v, vector<int>& wt, int src) {
    vector<int> dist(V, 1e9); // Initialize distances to "infinity"
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; ++i) {
        for (int j = 0; j < E; ++j) {
            if (dist[u[j]] != 1e9 && dist[u[j]] + wt[j] < dist[v[j]]) {
                dist[v[j]] = dist[u[j]] + wt[j];
            }
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < E; ++j) {
        if (dist[u[j]] != 1e9 && dist[u[j]] + wt[j] < dist[v[j]]) {
            cout << "Negative weight cycle detected!" << endl;
            return;
        }
    }

    // Print distances
    cout << "Vertex\tDistance from Source" << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << "\t" << dist[i] << endl;
    }
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<int> u(E), v(E), wt(E);

    cout << "Enter edges (u v wt):" << endl;
    for (int i = 0; i < E; ++i) {
        cin >> u[i] >> v[i] >> wt[i];
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    bellmanFord(V, E, u, v, wt, src);

    return 0;
}
