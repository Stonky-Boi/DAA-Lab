// Each node requires a minimum strength to activate, and each edge causes energy loss
// Determine the maximum number of nodes that can be activated

#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, int parent, long long current_dist, int current_count, int &activated_nodes,
         const vector<vector<pair<int, long long>>> &adj, const vector<long long> &t, long long s)
{
    if (current_dist > s || s - current_dist < t[node])
        return;
    current_count++;
    if (current_count > activated_nodes)
        activated_nodes = current_count;
    for (auto [neighbor, weight] : adj[node])
    {
        if (neighbor == parent)
            continue;
        dfs(neighbor, node, current_dist + weight, current_count, activated_nodes, adj, t, s);
    }
}

int main()
{
    int n;
    long long s;
    cin >> n >> s;
    vector<long long> t(n);
    for (long long &i : t)
        cin >> i;
    vector<vector<pair<int, long long>>> adj(n);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    int activated_nodes = 0;
    dfs(0, -1, 0, 0, activated_nodes, adj, t, s);
    cout << activated_nodes << endl;
    return 0;
}