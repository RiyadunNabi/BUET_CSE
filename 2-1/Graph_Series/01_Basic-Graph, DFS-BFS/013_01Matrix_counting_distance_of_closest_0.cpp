// https://leetcode.com/problems/01-matrix/submissions/1612598128/
// Given an m x n binary matrix mat, return the distance of the nearest 0 for each cell.
//The distance between two cells sharing a common edge is 1.

#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
        vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
            int n=mat.size(), m=mat[0].size();
            vector<vector<int>> dist(n,vector<int>(m,0));
            vector<vector<bool>> visited(n,vector<bool>(m,false));
            queue<pair<pair<int,int>,int>> q;
            for(int i=0; i<n; i++){
                for(int j=0; j<m; j++){
                    if(mat[i][j]==0){
                        q.push({{i,j},0});
                        visited[i][j]=true;
                    }
                }
            }
            vector<pair<int, int>> direction={{1,0},{0,1},{-1,0},{0,-1}};
            while(!q.empty()){
                auto cell=q.front();
                q.pop();
                int x=cell.first.first;
                int y=cell.first.second;
                int d=cell.second;
                for (int i = 0; i < 4; i++)
                {
                    int nextX=x+direction[i].first;
                    int nextY=y+direction[i].second;
                    if(nextX>=0 && nextX<n && nextY>=0 && nextY<m && !visited[nextX][nextY]){
                        dist[nextX][nextY]=d+1;
                        visited[nextX][nextY]=true;
                        q.push({{nextX,nextY},d+1});
                    }
                }
            }
            return dist;
        }
};

int main(){




    return 0;
}
