#include <bits/stdc++.h>
using namespace std;

void ListFromMatrix(int n,vector<vector<int>> &adjM){ 
    vector<vector<int>> adjL(n + 1);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (adjM[i][j] == 1 && i!=j) {
                adjL[i].push_back(j);
            }
        }
    }

    //or this one, will traverse only upper triangular matrix
    vector<vector<int>> adjL(n+1);
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j<n; j++)
        {
            if(adjM[i][j]==1){
                adjL[i+1].push_back(j+1);
                adjL[j+1].push_back(i+1);
            }
        }  
    }



    cout << "Adjacency List from Matrix:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int neighbor : adjL[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}


int main(){
    int n,m; // n=nodes, m=edges
    cin>>n>>m;

    //Adj Matrix
    vector<vector<int>> adjM(n + 1, vector<int>(n + 1, 0));

    //Adj List
    vector<vector<int>> adjL(n+1);
    for (int i = 1; i <=m; i++)
    {
        int u,v;
        cin>>u>>v;
        
        //adMatrix
        adjM[u][v]=1;
        adjM[v][u]=1;

        //adjList
        adjL[u].push_back(v);
        adjL[v].push_back(u);   //if directed graph, comment one of them;
    }


    // Output the adjacency Matrix
    cout << "Adjacency Matrix:" << endl;
    for (int i = 1; i <=n; i++){
        for(int j=1; j<=n; j++){
            cout<<adjM[i][j]<<" ";
        }
        cout<<endl;
    }

    // Output the adjacency list
    cout << "Adjacency List:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << i << ": ";
        for (int neighbor : adjL[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }

    ListFromMatrix(n,adjM);

    return 0;
}



/*

n=4 m=3


0 1 0 0
1 0 1 0
0 1 0 1
0 0 1 0

1 2
2 3
3 4

Adjacency List:
1: 2
2: 1 3
3: 2 4
4: 3

*/
