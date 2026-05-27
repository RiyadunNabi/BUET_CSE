#include <bits/stdc++.h>
using namespace std;

void dfs(int course, vector<vector<int>>& reverseAdjList, vector<bool>& visited, int& count) {
    visited[course] = true;
    for (int prereq : reverseAdjList[course]) {
        if (!visited[prereq]) {
            count++;
            dfs(prereq, reverseAdjList, visited, count);
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;
    
    // Reverse adjacency list
    vector<vector<int>> reverseAdjList(N + 1);
    for (int i = 0; i < M; i++) {
        int A, B;
        cin >> A >> B;
        reverseAdjList[B].push_back(A);  // B has a prerequisite A
    }
    
    int Q;
    cin >> Q;
    
    while (Q--) {
        int C;
        cin >> C;
        
        // Count prerequisites for course C
        vector<bool> visited(N + 1, false);
        int count = 0;
        dfs(C, reverseAdjList, visited, count);
        
        cout << count << endl;
    }
    
    return 0;
}
