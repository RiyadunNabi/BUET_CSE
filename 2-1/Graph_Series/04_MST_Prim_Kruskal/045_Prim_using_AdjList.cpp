// #include <iostream>
// #include <vector>
// #include <queue>
// #include <utility>
#include <bits/stdc++.h>
using namespace std;

void printMST(vector<int> &parent, vector<int> &key){
    int V=parent.size();
    cout << "Edges in the MST:\n";
    for (int i = 0; i < V; ++i) {
        if (parent[i] != -1)
            cout << parent[i] << " - " << i << " (Weight: " << key[i] << ")\n";
    }
}

int primMSTAdjList(int V, vector<vector<pair<int, int>>> &adj) {
    vector<bool> inMST(V, false);
    vector<int> key(V, INT_MAX);      
    vector<int> parent(V, -1);         

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    pq.push({0, 0}); // {weight, vertex}
    int totalWeight = 0;

    while (!pq.empty()) {
        // auto it=pq.top();
        int weight = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        //else
        inMST[u] = true;
        totalWeight += weight;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u; // Save the edge
                pq.push({w, v});
            }
        }
    }

    printMST(parent,key);

    return totalWeight;
}

void primMSTAdjList_using_Tuple_and_Storing_MST(int V, vector<vector<pair<int, int>>> &adj) {
    vector<bool> inMST(V, false);
    vector<int> key(V, INT_MAX);       // Min edge weight to reach each vertex
    vector<tuple<int,int,int>> MST;

    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;

    key[0] = 0;
    pq.push({0,-1,0});  //weight, parent, node
    int totalWeight = 0;

    while (!pq.empty()) {
        auto it=pq.top();
        int weight = get<0>(it);
        int par=get<1>(it);
        int u = get<2>(it);
        pq.pop();

        if (inMST[u]) continue;
        //else
        inMST[u] = true;
        totalWeight += weight;
        if (par != -1) {
            MST.push_back({weight, par, u});
        }

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                pq.push({w,u,v});
            }
        }
    }

    cout << "Edges in the Minimum Spanning Tree:\n";
    for (auto &t : MST) {        //C++17 --> const auto& [u, v, w] : edges
        int w, u, v;
        std::tie(w, u, v) = t;   
        cout << u << " - " << v << " (Weight: " << w << ")\n";
    }

    cout << "Total weight of MST: " << totalWeight << "\n";
}


int main() {
    int V, E;
    // cout << "Enter number of vertices and edges: ";
    // cin >> V >> E;

    vector<vector<pair<int, int>>> adj(V); // {neighbor, weight}

    // cout << "Enter edges in format: u v weight (0-based index)\n";
    // for (int i = 0; i < E; ++i) {
    //     int u, v, w;
    //     cin >> u >> v >> w;
    //     adj[u].push_back({v, w});
    //     adj[v].push_back({u, w}); // undirected graph
    // }

    V=5; E=6;
    // Add edges: (u, v, weight)
    adj[0].push_back({1, 2});
    adj[1].push_back({0, 2}); // since undirected

    adj[0].push_back({3, 6});
    adj[3].push_back({0, 6});

    adj[1].push_back({2, 3});
    adj[2].push_back({1, 3});

    adj[1].push_back({3, 8});
    adj[3].push_back({1, 8});

    adj[1].push_back({4, 5});
    adj[4].push_back({1, 5});

    adj[2].push_back({4, 7});
    adj[4].push_back({2, 7});

    int mstWeight = primMSTAdjList(V, adj);
    cout << "Total weight of MST: " << mstWeight << endl;

    primMSTAdjList_using_Tuple_and_Storing_MST(V, adj);

    return 0;
}

/* OUTPUT:

Edges in the MST:
0 - 1 (Weight: 2)
1 - 2 (Weight: 3)
0 - 3 (Weight: 6)
1 - 4 (Weight: 5)
Total weight of MST: 16
*/

/* 
do i really need key here?

DEEPSEEK IS THINKING...
Looking at the code here, they have a key vector initialized to INF,
and when processing edges, they check if the current edge weight is less than the key of the adjacent vertex. 
If so, they update the key and push it into the priority queue.

Wait, but in some implementations, I've seen people just use the priority queue without maintaining a separate key array. 
Oh right, but that can lead to duplicate entries in the priority queue. 
Because when you find a better (smaller) weight for a vertex that's already in the queue, you just add a new entry with the smaller weight. 
The older, larger weight entries are ignored because once the vertex is marked as inMST, those are skipped.

So in this code, the key array is used to track the minimum weight needed to add the vertex to the MST. 
By checking if the current edge's weight is less than the key[v], they ensure that they only push the smallest possible weight for each vertex into the queue. 
This way, the priority queue doesn't have multiple entries for the same vertex with different weights. 
That could reduce the number of elements in the priority queue, making it more efficient, especially in dense graphs.
*/



/* FINAL THOUGHTS...
The key array in your Prim's algorithm implementation serves two crucial purposes:

Optimization: It tracks the minimum edge weight required to connect each vertex to the MST. 
This avoids redundant entries in the priority queue by only pushing a vertex when a cheaper (smaller weight) connection is found. 
Without it, the priority queue could contain multiple outdated higher weights for the same vertex, 
leading to unnecessary processing (though correctness is maintained as outdated entries are skipped once the vertex is in the MST).

Storing MST Edge Weights: The key array holds the weight of the edge that connects each vertex to its parent in the MST. 
This is essential for correctly printing the MST edges with their weights. 
If removed, you'd need an alternative way to track these weights 
(like a separate structure or searching the adjacency list, which is inefficient).

Can you remove key?
Yes, but with trade-offs:
**Correctness: The algorithm would still work, as the priority queue ensures the smallest weight is processed first.
**Efficiency: The queue may have more entries, slightly impacting performance.
**Output: Printing MST edges with their weights becomes non-trivial without key, requiring extra steps to track edge weights (e.g., modifying parent to store weights).

Modified code without key (simplified for illustration):
int primMSTAdjList(int V, vector<vector<pair<int, int>>> &adj) {
    vector<bool> inMST(V, false);
    vector<int> parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, 0}); // {weight, vertex}
    int totalWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalWeight += weight;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (!inMST[v]) {
                // Always push, no key check
                parent[v] = u; // This might overwrite with non-minimal weights
                pq.push({w, v});
            }
        }
    }

    // To print edges, you'd need to find the actual weight from parent to child
    cout << "Edges in the MST (weights might be incorrect):\n";
    for (int i = 1; i < V; ++i) {
        if (parent[i] != -1) {
            // This part is inefficient without key[]
            int w = -1;
            for (auto &edge : adj[parent[i]]) {
                if (edge.first == i) {
                    w = edge.second;
                    break;
                }
            }
            cout << parent[i] << " - " << i << " (Weight: " << w << ")\n";
        }
    }

    return totalWeight;
}


Conclusion:
While you can remove key, it's not recommended. The key array optimizes the queue and simplifies output. 
Without it, you sacrifice efficiency and complicate edge weight retrieval. Keep key for a correct, efficient, and clean implementation.


*/
