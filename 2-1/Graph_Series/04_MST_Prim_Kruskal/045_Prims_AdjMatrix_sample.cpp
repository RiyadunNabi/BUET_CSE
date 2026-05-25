#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

const int MAX = 100;

int primMSTWithPQ(int graph[MAX][MAX], int V) {
    vector<bool> inMST(V, false);
    vector<int> key(V, INT_MAX);

    // Min-heap: (weight, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0}); // Start from vertex 0

    int totalWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalWeight += weight;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                pq.push({key[v], v});
            }
        }
    }

    return totalWeight;
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    int graph[MAX][MAX];
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            cin >> graph[i][j];

    int mstWeight = primMSTWithPQ(graph, V);
    cout << "Total weight of MST: " << mstWeight << endl;

    return 0;
}




//AdjMatrix
/* #include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAX = 100; // adjust as needed

int primMST(int graph[MAX][MAX], int V) {
    vector<int> key(V, INT_MAX);   // Minimum weights to add each vertex
    vector<bool> inMST(V, false);  // Track included vertices
    key[0] = 0;                    // Start from vertex 0
    int totalWeight = 0;

    for (int count = 0; count < V; ++count) {
        int u = -1;

        // Find the vertex with the minimum key value not yet included
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && (u == -1 || key[v] < key[u]))
                u = v;
        }

        inMST[u] = true;
        totalWeight += key[u];

        // Update key values of adjacent vertices
        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
            }
        }
    }

    return totalWeight;
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    int graph[MAX][MAX];
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            cin >> graph[i][j];

    int mstWeight = primMST(graph, V);
    cout << "Total weight of MST: " << mstWeight << endl;

    return 0;
}
*/
