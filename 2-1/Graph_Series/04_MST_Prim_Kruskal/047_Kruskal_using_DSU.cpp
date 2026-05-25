// #include <iostream>
// #include <vector>
// #include <algorithm>
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// bool compareEdges(const Edge& e1, const Edge& e2) {
//     return e1.weight < e2.weight;
// }

class DisjointSetUnion {
    vector<int> parent, rank;
public:
    DisjointSetUnion(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int findSet(int u) {
        if (parent[u] != u)
            parent[u] = findSet(parent[u]);
        return parent[u];
    }

    bool unionSets(int u, int v) {
        int parentU = findSet(u);
        int parentV = findSet(v);
        if (parentU == parentV) return false;

        if (rank[parentU] < rank[parentV])
            parent[parentU] = parentV;
        else {
            parent[parentV] = parentU;
            if (rank[parentU] == rank[parentV])
                rank[parentU]++;
        }
        return true;
    }
};

void printMST(vector<Edge>& mstEdges){
    for (const auto& edge : mstEdges) {
        cout << edge.u << " " << edge.v << " " << edge.weight << "\n";
    }
}

int kruskalMST(int v, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());
    // sort(edges.begin(), edges.end(), compareEdges);

    DisjointSetUnion dsu(v);
    int totalMstWeight = 0;
    vector<Edge> mstEdges;

    for (const auto& edge : edges) {
        if (dsu.unionSets(edge.u, edge.v)) {
            totalMstWeight += edge.weight;
            mstEdges.push_back(edge);
        }
    }

    return totalMstWeight;
}

int main() {
    int v, e;
    cin >> v >> e;

    vector<Edge> edges(e);
    for (int i = 0; i < e; ++i) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    int totalWeight = kruskalMST(v, edges);
    cout << totalWeight << "\n";

    return 0;
}
