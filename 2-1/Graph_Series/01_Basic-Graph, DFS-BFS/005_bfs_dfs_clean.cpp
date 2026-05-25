#include <bits/stdc++.h>
using namespace std;


class SolutionBFSinOneFunc {
public:
    vector<int> bfsDisconnected(int n, vector<vector<int>> adjL) {
        vector<bool> visited(n, false); 
        vector<int> bfsList;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                visited[i] = true;
                queue<int> q;
                q.push(i);

                while (!q.empty()) {
                    int u = q.front();
                    q.pop();
                    bfsList.push_back(u);

                    for (int v : adjL[u]) {   //for(int v=0; v<M.size(); v++){
                        if (!visited[v]) {    //    if(M[u][v]==1 && !visited[v])
                            visited[v] = true;
                            q.push(v);
                        }
                    }
                }
            }
        }
        return bfsList;
    }
};

class SolutionBFS{
    private:
    void bfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &bfsList, int node){  //there are two times if(!visited[]) visited[]=true; it is prefferable
        visited[node] = true;
        queue<int> q;
        q.push(node);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            bfsList.push_back(u);

            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    public:
    vector<int> bfsDisconnected(int n, vector<vector<int>> adj) {
        vector<bool> visited(n + 1, false); 
        vector<int> bfsList;  
        
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                bfs(adj, visited, bfsList, i);
            }
        }
        return bfsList;
    }
};

class SolutionDFS{
    private:
    void dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &dfsList, int u){
        visited[u]=true;
        dfsList.push_back(u);

        for(int v : adj[u]){
            if(!visited[v]){
                dfs(adj, visited, dfsList, v);
            }
        }
    }

    public:
    vector<int> dfsDisconnected(int n, vector<vector<int>> adj){
        vector<bool> visited(n, false);
        vector<int> dfsList;

        for(int i=0; i<n; i++){
            if(!visited[i]){
                dfs(adj, visited, dfsList, i);
            }
        }

        return dfsList;
    }

};


int main() {

    int n = 6;  // Number of nodes
    vector<vector<int>> adj(n + 1);

    // Add edges for a graph with multiple components
    adj[1].push_back(2);
    adj[2].push_back(1);

    adj[3].push_back(4);
    adj[4].push_back(3);

    adj[5].push_back(6);
    adj[6].push_back(5);

    // BFS Traversal
    SolutionBFS solbfs;
    vector<int> bfsResult = solbfs.bfsDisconnected(n, adj);
    cout << "BFS Traversal: ";
    for (int node : bfsResult) {
        cout << node << " ";
    }
    cout << endl;

    // DFS Traversal
    SolutionDFS soldfs;
    vector<int> dfsResult = soldfs.dfsDisconnected(n, adj);
    cout << "DFS Traversal: ";
    for (int node : dfsResult) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
    
