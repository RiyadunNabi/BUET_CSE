#include <bits/stdc++.h>
using namespace std;

// so, if cycle is found, print false, otherwise false

class Solution
{

private:
    bool dfs(int numCourses, vector<vector<int>> &adjL, vector<int> &color, int u)
    {
        color[u] = 0;
        for (int v : adjL[u])
        {
            if (color[v] == -1)
            {
                if(! dfs(numCourses, adjL, color, v)){
                    return false;
                }
            }
            else if (color[v] == 0)
            {
                return false;
            }
        }
        color[u] = 1;
        return true;
    }

public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> adjL(numCourses);
        for (auto pair : prerequisites)
        {
            adjL[pair[0]].push_back(pair[1]);
        }

        vector<int> color(numCourses, -1);
        for (int i = 0; i < numCourses; i++)
        {
            if (color[i] == -1)
            {
                if(!dfs(numCourses, adjL, color, i)){
                    return false;
                }
            }
        }
        return true;
    }
};

int main()
{

    return 0;
}

/*

207. Course Schedule
Medium
Topics
Companies
Hint
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.



Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take.
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.


Constraints:

1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
All the pairs prerequisites[i] are unique.


*/
