//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
    private:
    vector<pair<int, int>> del={{-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1}};
    void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j){
        int n=grid.size();
        int m=grid[0].size();

        visited[i][j]=true;
        queue<pair<int,int>> q;
        q.push({i,j});
        while (!q.empty()){
            pair<int, int> p=q.front();
            q.pop();
            for(int k=0; k<8; k++){
                int x=p.first + del[k].first;
                int y=p.second + del[k].second;
                if((x>=0 && y>=0 && x<n && y<m) && !visited[x][y] && grid[x][y]=='1'){
                    visited[x][y]=true;
                    q.push({x,y});
                }
            }
        } 
    }
    
  public:
    // Function to find the number of islands.
    int numIslands(vector<vector<char>>& grid) {
        int n=grid.size();
        int m=grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        int island=0;
        for (int i = 0; i < n; i++)
        {
            for(int j=0; j<m; j++){
                if(grid[i][j]=='1' && visited[i][j]==false){
                    island++;
                    bfs(grid,visited,i,j);
                }
            }
        }
        return island;
    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<vector<char>> grid(n, vector<char>(m, '#'));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> grid[i][j];
            }
        }
        Solution obj;
        int ans = obj.numIslands(grid);
        cout << ans << '\n';
    
cout << "~" << "\n";
}
    return 0;
}
// } Driver Code Ends
