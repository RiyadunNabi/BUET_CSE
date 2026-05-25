#include <bits/stdc++.h>
using namespace std;

class Solution{
    private:
    void dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &dfsList, int node){
        visited[node]=true;
        dfsList.push_back(node);

        for(int v : adj[node]){
            if(!visited[v]){
                dfs(adj, visited, dfsList, v);
            }
        }
    }

    void bfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &bfsList, int node){  //there are two times if(!visited[]) visited[]=true; it is prefferable
        visited[node] = true;
        queue<int> q;
        q.push(node);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            bfsList.push_back(node);

            for (int v : adj[node]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    void bfs2(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &bfsList, int node){ //there are one time if(!visited[]) visited[]=true;
        queue<int> q;
        q.push(node);

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            visited[node] = true;
            bfsList.push_back(node);

            for (int v : adj[node]) {
                if (!visited[v]) {
                    q.push(v);
                }
            }
        }
    }


    public:

    //If the graph is disconnected, this implementation only traverses the connected component starting from node
    vector<int> bfsConnected(int n, vector<vector<int>> &adj){
        vector<bool> visited(n + 1, false);
        vector<int> bfsList;

        bfs(adj, visited, bfsList, 1);

        return bfsList;
    }

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

    vector<int> dfsConnected(int n, vector<vector<int>> adj){
        vector<bool> visited(n+1, false);
        vector<int> dfsList;

        dfs(adj, visited, dfsList, 1);

        return dfsList;

    }

    vector<int> dfsDisconnected(int n, vector<vector<int>> adj){
        vector<bool> visited(n+1, false);
        vector<int> dfsList;

        for(int i=1; i<=n; i++){
            if(!visited[i]){
                dfs(adj, visited, dfsList, i);
            }
        }

        return dfsList;

    }
};

/***********************************************************************************************************/ //dfs part
//this is prefferable
class SolutionDFS1{
    private:
    void dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &dfsList, int node){
        visited[node]=true;
        dfsList.push_back(node);

        for(int v : adj[node]){
            if(!visited[v]){
                dfs(adj, visited, dfsList, v);
            }
        }
    }

    public:
    vector<int> dfsDisconnected(int n, vector<vector<int>> adj){
        vector<bool> visited(n+1, false);
        vector<int> dfsList;

        for(int i=1; i<=n; i++){
            if(!visited[i]){
                dfs(adj, visited, dfsList, i);
            }
        }

        return dfsList;
    }

};
/***********************************************************************************************************/

class SolutionDFS2{
    private:
    void dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &dfsList, int node){
        dfsList.push_back(node);

        for(int v : adj[node]){
            if(!visited[v]){
                visited[v]=true;
                dfs(adj, visited, dfsList, v);
            }
        }
    }

    public:
    vector<int> dfsDisconnected(int n, vector<vector<int>> adj){
        vector<bool> visited(n+1, false);
        vector<int> dfsList;

        for(int i=1; i<=n; i++){
            if(!visited[i]){
                visited[i]=true;
                dfs(adj, visited, dfsList, i);
            }
        }

        return dfsList;
    }

};

/*
1 - 2

3 - 4

5 - 6
*/

int main() {
    Solution sol;

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
    vector<int> bfsResult = sol.bfsDisconnected(n, adj);
    cout << "BFS Traversal: ";
    for (int node : bfsResult) {
        cout << node << " ";
    }
    cout << endl;

    // DFS Traversal
    vector<int> dfsResult = sol.dfsDisconnected(n, adj);
    cout << "DFS Traversal: ";
    for (int node : dfsResult) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
