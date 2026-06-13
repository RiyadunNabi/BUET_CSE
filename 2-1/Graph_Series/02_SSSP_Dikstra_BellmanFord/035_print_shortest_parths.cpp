#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<int> dijkstra(int n, vector<vector<int>>& edges, int source, int destination) {
            vector<pair<int,int>> adj[n+1];
            for(auto it: edges) {
                adj[it[0]].push_back({it[1], it[2]});
                adj[it[1]].push_back({it[0], it[2]});
            }
    
            priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
            vector<int> dist(n+1, INT_MAX);
            vector<int> parent(n+1);  // to store the path
            
            for(int i = 0; i <= n; i++) parent[i] = i; // initially each node is its own parent
            
            pq.push({0, source});
            dist[source] = 0;
            
            while(!pq.empty()) {            
                int distance = pq.top().first;
                int u = pq.top().second;
                pq.pop();
                
                for(auto adjacentNode: adj[u]) {
                    int v = adjacentNode.first;
                    int w = adjacentNode.second;
                    
                    if(distance + w < dist[v]) {
                        dist[v] = distance + w;
                        pq.push({dist[v], v});
                        parent[v] = u;  // update parent
                    }
                }
            }
    
            // Now recover the path from source to destination
            vector<int> path;
            int node = destination;
            if(dist[node] == INT_MAX) {
                return {-1}; // No path exists
            }
            while(parent[node] != node) { // Until we reach the source
                path.push_back(node);
                node = parent[node];
            }
            path.push_back(source);
            reverse(path.begin(), path.end()); // because we stored from destination -> source
            
            return path;
        }
    };
    

int main(){




    return 0;
}