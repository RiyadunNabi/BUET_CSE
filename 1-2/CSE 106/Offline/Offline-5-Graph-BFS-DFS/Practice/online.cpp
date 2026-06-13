#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
vector<vector<bool>> visited;
vector<pair<int,int>> pairs;
set<pair<int,int>> reachableExits;
pair<int,int> size;

const int dx[] = { -1, 1, 0, 0 };
const int dy[] = { 0, 0, -1, 1 };

void dfs(pair<int,int> start)
{
    visited[start.first][start.second]=true;

    if(grid[start.first][start.second]=='E')
    {
        reachableExits.insert({start.first, start.second});
    }

    for (int i = 0; i < 4; i++)
    {
        // int nx=start.first=start.first+dx[i];
        // int ny=start.second=start.second+dy[i];
        
        int nx=start.first+dx[i];
        int ny=start.second+dy[i];

        if(nx>=0 && nx<size.first && ny>=0 && ny<size.second && !visited[nx][ny] && grid[nx][ny]!='#')
        {
            dfs({nx,ny});
        }
    }
    
}

int main()
{
    int n, m;
    cin>>n>>m;
    size.first=n;
    size.second=m;
    // grid.resize(n);
    bool foundStart=false;
    pair<int,int> start;
    for (int i = 0; i < n; i++)
    {
        string s;
        cin>>s;
        grid.push_back(s);
        for (int j = 0; !foundStart && j < m; j++)
        {
            if(grid[i][j]=='S')
            {
                start={i,j};
                foundStart=true;
            }
        }     
    }
    visited.resize(n, vector<bool>(m, false));

    dfs(start);

    cout<<reachableExits.size()<<endl;
    
}

// 5 5
// S....
// .###E
// .#..#
// ...E.
// E.#..


// 6 6
// S.#..E
// .#.##.
// ..#..#
// .##..E
// .#....
// E.#.##