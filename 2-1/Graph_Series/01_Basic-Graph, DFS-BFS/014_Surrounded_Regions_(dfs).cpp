#include <bits/stdc++.h>
using namespace std;

class Solution{
    public:
    int direction[4][2]={{-1,0},{1,0},{0,1},{0,-1}};
    void solve(vector<vector<char>> &board){
        int r=board.size();
        int c=board[0].size();
        
        vector<vector<bool>> visited(r, vector<bool>(c, false));
        for (int i = 0; i < r; i++){
            if(board[i][0]=='O' && !visited[i][0]){
                dfs(board, visited,r,c, i,0);
            }
        }

        for (int i = 0; i < r; i++){
            if(board[i][c-1]=='O' && !visited[i][c-1]){
                dfs(board, visited,r,c, i,c-1);
            }
        }

        for (int i = 0; i < c; i++){
            if(board[0][i]=='O' && !visited[0][i]){
                dfs(board, visited,r,c, 0,i);
            }
        }

        for (int i = 0; i < c; i++){
            if(board[r-1][i]=='O' && !visited[r-1][i]){
                dfs(board, visited,r,c, r-1,i);
            }
        }

        for (int i = 0; i < r; i++)
        {
            for(int j=0; j<c; j++){
                if(board[i][j]=='O' && !visited[i][j]){
                    board[i][j]='X';
                }
            }
        }
        
        
    }
    private:
    void dfs(vector<vector<char>> &board, vector<vector<bool>> & visited, int r, int c, int x, int y){
        visited[x][y]=true;
        for (int i = 0; i < 4; i++)
        {
            int nx=x+direction[i][0];
            int ny=y+direction[i][1];
            if(nx>=0 && ny>=0 && nx<r && ny<c && board[nx][ny]=='O' && !visited[nx][ny]){
                dfs(board,visited,r,c,nx,ny);
            }
        }
        
    }
};

int main()
{

    return 0;
}
