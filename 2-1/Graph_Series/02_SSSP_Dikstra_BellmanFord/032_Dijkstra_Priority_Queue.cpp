#include <bits/stdc++.h>
using namespace std;


// max-heap : priority_queue<int> pq;
// min-heap : priority_queue<int, vector<int>, greater<int>> pq;

// greater<pair<int, int>> →
// This says:
// When comparing two pairs, smaller comes first.
// First compare by first, and if equal, compare by second.
// list of (distance, node) pairs.


class solution{
    public:
    vector<int> dijkstra(int n, vector<vector<int>>& edges, int source){
        vector<pair<int,int>> adj[n+1];
        for(auto it: edges){
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }

        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        vector<int> dist(n+1, INT_MAX);
        
        pq.push({0, source});
        dist[source] = 0;
        
        while(!pq.empty()){            
            int distance = pq.top().first; 
            int u = pq.top().second;
            pq.pop();
            
            for(auto adjacentNode: adj[u]){
                int v = adjacentNode.first;
                int w = adjacentNode.second;
                
                if(distance + w < dist[v]){
                    dist[v] = distance + w;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
};

int main(){




    return 0;
}