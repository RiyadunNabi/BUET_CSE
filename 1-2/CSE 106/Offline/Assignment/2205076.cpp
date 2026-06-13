#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int weight, u, v;
    Edge(int w, int x, int y) {
        weight=w;
        u=x;
        v=y;
    }
};

bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

class UnionFindRoot {
private:
    vector<int> parentOf, rankOf;
public:
    UnionFindRoot(int n) {
        parentOf.resize(n);
        rankOf.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parentOf[i] = i;
        }
    }

    int findRoot(int x) {
        if (parentOf[x] != x) {
            parentOf[x] = findRoot(parentOf[x]);
        }
        return parentOf[x];
    }

    bool unite(int x, int y) {
        int rootX = findRoot(x);
        int rootY = findRoot(y);
        if (rootX == rootY) return false;

        if (rankOf[rootX] > rankOf[rootY]) {
            parentOf[rootY] = rootX;
        }
        else if (rankOf[rootX] < rankOf[rootY]) {
            parentOf[rootX] = rootY;
        }
        else {
            parentOf[rootY] = rootX;
            rankOf[rootX]++;
        }
        return true;
    }
};

int countMSTWeight(int n, vector<Edge>& edges) {

    sort(edges.begin(), edges.end(), compareEdges);

    UnionFindRoot uf(n);
    int mstWeight = 0;

    for (Edge edge : edges) {
        if (uf.unite(edge.u, edge.v)) {
            mstWeight += edge.weight;
        }
    }

    return mstWeight;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input.is_open() || !output.is_open()) {
        cerr << "Error: Could not open file." << endl;
        return 1;
    }

    int n, m;
    input >> n >> m;

    vector<Edge> edges;
    for (int i = 0; i < m; i++) {
        int w, u, v;
        input >> w >> u >> v;
        edges.emplace_back(w, u, v);
    }

    int MSTWeight = countMSTWeight(n, edges);

    output << MSTWeight << endl;

    input.close();
    output.close();
    return 0;
}
