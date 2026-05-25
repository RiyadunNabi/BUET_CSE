//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends
class Solution {

    private:
    vector<vector<int>> d={{0,-1},{0,1},{-1,0},{1,0}};
    void dfs(vector<vector<int>>& result, vector<vector<bool>> &visited, int sr, int sc, int oldColor, int newColor){
        visited[sr][sc]=true;
        result[sr][sc]=newColor;
        for (int i = 0; i < 4; i++)
        {
            int x=sr+d[i][0];
            int y=sc+d[i][1];
            if(x>=0 && y>=0 && x<result.size() && y<result[0].size() && !visited[x][y] && result[x][y]==oldColor){
                dfs(result,visited,x,y,oldColor,newColor);
            }
        }
        
    }
  public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        int oldColor=image[sr][sc];
        int n=image.size();
        int m=image[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        vector<vector<int>>result(image);

        dfs(result,visited,sr,sc,oldColor,newColor);

        return result;

    }
};

//{ Driver Code Starts.
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> image(n, vector<int>(m, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                cin >> image[i][j];
        }
        int sr, sc, newColor;
        cin >> sr >> sc >> newColor;
        Solution obj;
        vector<vector<int>> ans = obj.floodFill(image, sr, sc, newColor);
        for (auto i : ans) {
            for (auto j : i)
                cout << j << " ";
            cout << "\n";
        }

        cout << "~"
             << "\n";
    }
    return 0;
}
// } Driver Code Ends
