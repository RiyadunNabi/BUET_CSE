#include <bits/stdc++.h>
using namespace std;

// ─── Hash for vector<int> so we can use it in unordered_map/set ───
struct VectorHash {
    size_t operator()(const vector<int>& v) const {
        size_t seed = v.size();
        for (auto& i : v)
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

int K; // grid size (3 for 8-puzzle, 4 for 15-puzzle)

// ─── Goal state ───
vector<int> getGoal() {
    vector<int> goal(K * K);
    iota(goal.begin(), goal.end(), 1);  // fill 1,2,3,...,k*k
    goal[K * K - 1] = 0;               // last cell is blank
    return goal;
}

// ─── Get neighbors ───
vector<vector<int>> getNeighbors(const vector<int>& board) {
    vector<vector<int>> neighbors;

    int blank = find(board.begin(), board.end(), 0) - board.begin();
    int row = blank / K, col = blank % K;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int d = 0; d < 4; d++) {
        int nr = row + dr[d];
        int nc = col + dc[d];

        if (nr < 0 || nr >= K || nc < 0 || nc >= K) continue;

        int newBlank = nr * K + nc;
        vector<int> next = board;
        swap(next[blank], next[newBlank]);
        neighbors.push_back(next);
    }

    return neighbors;
}

// ─── Heuristics ───
int hamming(const vector<int>& board) {
    int count = 0;
    for (int i = 0; i < K * K; i++) {
        if (board[i] != 0 && board[i] != i + 1)
            count++;
    }
    return count;
}

int manhattan(const vector<int>& board) {
    int dist = 0;
    for (int i = 0; i < K * K; i++) {
        if (board[i] == 0) continue;
        int tile = board[i] - 1;        // tile 1 should be at index 0
        int cur_row = i / K,    cur_col = i % K;
        int goal_row = tile / K, goal_col = tile % K;
        dist += abs(cur_row - goal_row) + abs(cur_col - goal_col);
    }
    return dist;
}

double euclidean(const vector<int>& board) {
    double dist = 0;
    for (int i = 0; i < K * K; i++) {
        if (board[i] == 0) continue;
        int tile = board[i] - 1;
        int cur_row = i / K,    cur_col = i % K;
        int goal_row = tile / K, goal_col = tile % K;
        int dr = cur_row - goal_row;
        int dc = cur_col - goal_col;
        dist += sqrt(dr*dr + dc*dc);
    }
    return dist;
}

int linearConflict(const vector<int>& board) {
    int conflicts = 0;

    // check each row
    for (int r = 0; r < K; r++) {
        for (int c1 = 0; c1 < K; c1++) {
            int t1 = board[r * K + c1];
            if (t1 == 0) continue;
            int goal_row_t1 = (t1 - 1) / K;
            if (goal_row_t1 != r) continue;   // t1 doesn't belong in this row

            for (int c2 = c1 + 1; c2 < K; c2++) {
                int t2 = board[r * K + c2];
                if (t2 == 0) continue;
                int goal_row_t2 = (t2 - 1) / K;
                if (goal_row_t2 != r) continue; // t2 doesn't belong in this row

                int goal_col_t1 = (t1 - 1) % K;
                int goal_col_t2 = (t2 - 1) % K;

                // t1 is left of t2 now, but t1's goal is right of t2's goal → conflict
                if (goal_col_t1 > goal_col_t2)
                    conflicts++;
            }
        }
    }

    // check each column (same logic)
    for (int c = 0; c < K; c++) {
        for (int r1 = 0; r1 < K; r1++) {
            int t1 = board[r1 * K + c];
            if (t1 == 0) continue;
            int goal_col_t1 = (t1 - 1) % K;
            if (goal_col_t1 != c) continue;

            for (int r2 = r1 + 1; r2 < K; r2++) {
                int t2 = board[r2 * K + c];
                if (t2 == 0) continue;
                int goal_col_t2 = (t2 - 1) % K;
                if (goal_col_t2 != c) continue;

                int goal_row_t1 = (t1 - 1) / K;
                int goal_row_t2 = (t2 - 1) / K;

                if (goal_row_t1 > goal_row_t2)
                    conflicts++;
            }
        }
    }

    return manhattan(board) + 2 * conflicts;
}

// ─── A* ───
using HeuristicFn = function<double(const vector<int>&)>;

struct Node {
    double f;
    int g;
    vector<int> board;

    bool operator>(const Node& other) const {
        return f > other.f;   // min-heap by f
    }
};

pair<int, vector<vector<int>>> solve(
    const vector<int>& initial,
    HeuristicFn heuristic,
    double W = 1.0
) {
    vector<int> goal = getGoal();

    unordered_map<vector<int>, vector<int>, VectorHash> parent;
    unordered_map<vector<int>, int, VectorHash> gScore;

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    double h0 = heuristic(initial);
    pq.push({0 + W * h0, 0, initial});
    gScore[initial] = 0;
    parent[initial] = {};   // start has no parent

    while (!pq.empty()) {
        auto [f, g, board] = pq.top();
        pq.pop();

        // skip if we already found a better path to this state
        if (gScore.count(board) && g > gScore[board]) continue;

        if (board == goal) {
            // reconstruct path
            vector<vector<int>> path;
            vector<int> cur = goal;
            while (!cur.empty()) {
                path.push_back(cur);
                cur = parent[cur];
            }
            reverse(path.begin(), path.end());
            return {g, path};
        }

        for (auto& neighbor : getNeighbors(board)) {
            int newG = g + 1;
            if (!gScore.count(neighbor) || newG < gScore[neighbor]) {
                gScore[neighbor] = newG;
                parent[neighbor] = board;
                double newF = newG + W * heuristic(neighbor);
                pq.push({newF, newG, neighbor});
            }
        }
    }

    return {-1, {}};   // unsolvable
}

// ─── Print board ───
void printBoard(const vector<int>& board) {
    for (int i = 0; i < K * K; i++) {
        if (board[i] == 0) cout << "_ ";
        else cout << board[i] << " ";
        if ((i + 1) % K == 0) cout << "\n";
    }
    cout << "\n";
}

// ─── Main ───
int main() {
    cin >> K;

    vector<int> initial(K * K);
    for (int i = 0; i < K * K; i++) cin >> initial[i];

    // pick heuristic here — just swap the lambda
    HeuristicFn heuristic = [](const vector<int>& b) {
        return (double)linearConflict(b);   // change to hamming/manhattan/euclidean
    };

    double W = 1.0;  // change for weighted A*

    auto [cost, path] = solve(initial, heuristic, W);

    if (cost == -1) {
        cout << "Unsolvable puzzle\n";
    } else {
        cout << "Minimum number of moves = " << cost << "\n\n";
        for (auto& board : path)
            printBoard(board);
    }

    return 0;
}









/*
To switch heuristics, just change this one line in main:

// Manhattan
HeuristicFn heuristic = [](const vector<int>& b) { return (double)manhattan(b); };

// Hamming
HeuristicFn heuristic = [](const vector<int>& b) { return (double)hamming(b); };

// Euclidean
HeuristicFn heuristic = [](const vector<int>& b) { return euclidean(b); };

// Linear Conflict
HeuristicFn heuristic = [](const vector<int>& b) { return (double)linearConflict(b); };

// Weighted A* — just change W
double W = 2.0;


*/