#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> SpaceStation(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        SpaceStation[u][v] = 1;
        SpaceStation[v][u] = 1;
    }
    vector<int> visited(n + 1, 0);
    vector<int> components;

    for (int u = 1; u <= n; u++)
    {
        if (visited[u] == 0)
        {
            components.push_back(u);

            queue<int> q;
            q.push(u);
            visited[u] = 1;
            cout << u << " ";

            while (!q.empty())
            {
                int vertex = q.front();
                q.pop();

                for (int i = 1; i <= n; i++)
                {
                    if (SpaceStation[vertex][i] == 1 && visited[i] == 0)
                    {
                        visited[i] = 1;
                        cout << i << " ";
                        q.push(i);
                    }
                }
            }
        }
    }
    cout << "\n\n";

    int k=components.size()-1;
    cout << k << endl;

    for (int i = 0; i < components.size()-1; i++)
    {
        cout<<components[i]<<" "<<components[i+1]<<endl;
    }
    return 0;
}
