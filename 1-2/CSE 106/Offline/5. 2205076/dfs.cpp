#include <iostream>
#include <vector>
// #include <queue>
using namespace std;

void dfs(int start, vector<vector<int>> &SpaceStation, vector<int>& visited)
{
    visited[start]=1;
    for (int j = 0; j < SpaceStation[start].size(); j++)
    {
        if(visited[SpaceStation[start][j]]==0)
        {
            dfs(SpaceStation[start][j], SpaceStation, visited);
        }
    } 
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> SpaceStation(n+1);
    for (int i = 0; i < m; i++)
    {
        int u,v;
        cin>>u>>v;
        SpaceStation[u].push_back(v);
        SpaceStation[v].push_back(u);
    }
    vector<int> visited(n+1,0);
    vector<int> components;

    for (int u = 1; u <= n; u++)
    {
        if(visited[u]==0)
        {
            components.push_back(u);
            dfs(u,SpaceStation,visited);
        }
    }

    int k=components.size()-1;
    cout<<k<<endl;

    for (int i = 0; i < components.size()-1; i++)
    {
        cout<<components[i]<<" "<<components[i+1]<<endl;
    }

    return 0;
}