
#include <bits/stdc++.h>
#include <vector>
using namespace std;

void bellmanFord(vector<int> &capitals, vector<int> &posts,vector<tuple<int,int,int>> &edges, int n,int m,int b) {
    vector<int> dist(n+1, 1e9); // Initialize distances to "infinity"
    for (int c : capitals) {
        dist[c] = 0;
    }  

    for (int i = 1; i <= n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            // auto [u, v, w] = edges[j];
            int u, v, w;
            tie(u, v, w) = edges[j];

            if(u==-1) continue;
            if (dist[u] != 1e9 && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    for (int j = 0; j < m; ++j) {
        // auto [u, v, w] = edges[j];
        int u, v, w;
        tie(u, v, w) = edges[j];

        if(u==-1) continue;
        if (dist[u] != 1e9 && dist[u] + w < dist[v]) {
            cout << "Abyss Detected" << endl;
            return;
        }
    }

    for (int i = 0; i < posts.size(); ++i) {
        if(dist[posts[i]]==1e9) {
            cout<<"INF"<<endl;
            continue;
        }

        cout << dist[posts[i]] << endl;
    }
}

int main() {
    int n,m,k,b,e;
    cin>>n>>m>>k>>b>>e;

    vector<int> capitals;
    for (int i = 0; i < k; i++)
    {
        int c;
        cin>>c;
        capitals.push_back(c);
    }

    vector<int> blocked;
    for (int i = 0; i < b; i++)
    {
        int c;
        cin>>c;
        blocked.push_back(c);
    }

    vector<int> posts;
    for (int i = 0; i < e; i++)
    {
        int c;
        cin>>c;
        posts.push_back(c);
    }

    vector<tuple<int,int,int>> edges;
    for (int i = 0; i < m; ++i) {
        int u,v,w;
        cin >> u>>v>>w;

        bool isBlocked = false;
        for (int j = 0; j < b; j++)
        {
            if(u==blocked[j] || v==blocked[j]){
                edges.push_back(make_tuple(-1,-1,-1));
                isBlocked = true;
                break;
            }
        }
        if (!isBlocked) {
            edges.push_back(make_tuple(u, v, w));
        }
    }

    bellmanFord(capitals, posts,edges,n,m,b);

    return 0;
}

/* DEEP SEEK

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, b, e;
    cin >> n >> m >> k >> b >> e;

    vector<int> capitals(k);
    for (int i = 0; i < k; ++i) {
        cin >> capitals[i];
    }

    unordered_set<int> blocked_set;
    for (int i = 0; i < b; ++i) {
        int c;
        cin >> c;
        blocked_set.insert(c);
    }

    vector<int> posts(e);
    for (int i = 0; i < e; ++i) {
        cin >> posts[i];
    }

    vector<vector<pair<int, int>>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        if (blocked_set.count(u) || blocked_set.count(v)) {
            continue;
        }
        adj[u].emplace_back(v, w);
    }

    const long long INF = 1e18;
    vector<long long> dist(n + 1, INF);
    queue<int> q;
    vector<int> cnt(n + 1, 0);
    vector<bool> in_queue(n + 1, false);
    int nodes_in_graph = n - blocked_set.size();

    for (int c : capitals) {
        if (!blocked_set.count(c)) {
            dist[c] = 0;
            q.push(c);
            in_queue[c] = true;
            cnt[c]++;
        }
    }

    bool abyss_detected = false;

    while (!q.empty() && !abyss_detected) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (auto &edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                if (!in_queue[v]) {
                    cnt[v]++;
                    if (cnt[v] > nodes_in_graph) {
                        abyss_detected = true;
                        break;
                    }
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }

    if (abyss_detected) {
        cout << "Abyss Detected" << endl;
        return 0;
    }

    for (int post : posts) {
        if (blocked_set.count(post)) {
            cout << "INF" << endl;
        } else if (dist[post] == INF) {
            cout << "INF" << endl;
        } else {
            cout << dist[post] << endl;
        }
    }

    return 0;
} */


/*
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, b, e;
    cin >> n >> m >> k >> b >> e;

    vector<int> capitals(k);
    for (int i = 0; i < k; ++i) {
        cin >> capitals[i];
    }

    unordered_set<int> blocked;
    for (int i = 0; i < b; ++i) {
        int c;
        cin >> c;
        blocked.insert(c);
    }

    vector<int> posts(e);
    for (int i = 0; i < e; ++i) {
        cin >> posts[i];
    }

    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        if (blocked.count(u) || blocked.count(v)) {
            continue;
        }
        edges.emplace_back(u, v, w);
    }

    const long long INF = 1e18;
    vector<long long> dist(n + 1, INF);
    for (int c : capitals) {
        if (!blocked.count(c)) {
            dist[c] = 0;
        }
    }

    // Bellman-Ford iterations
    for (int i = 1; i <= n - 1; ++i) {
        bool updated = false;
        for (const auto& edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int w = get<2>(edge);
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = true;
            }
        }
        if (!updated) {
            break; // Early exit if no updates
        }
    }

    // Check for negative cycles
    bool abyss = false;
    for (const auto& edge : edges) {
        int u = get<0>(edge);
        int v = get<1>(edge);
        int w = get<2>(edge);
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            abyss = true;
            break;
        }
    }

    if (abyss) {
        cout << "Abyss Detected" << endl;
        return 0;
    }

    // Output results
    for (int post : posts) {
        if (blocked.count(post)) {
            cout << "INF" << endl;
        } else if (dist[post] == INF) {
            cout << "INF" << endl;
        } else {
            cout << dist[post] << endl;
        }
    }

    return 0;
}





*/
