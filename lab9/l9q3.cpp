#include <iostream>
#include <vector>
using namespace std;

struct edge
{
    int to;
    long long weight;
};

void dfs1(int u, int parent, vector<vector<edge>> &adj, vector<long long> &dp,
          vector<int> &subtree_size)
{
    subtree_size[u] = 1;
    dp[u] = 0;
    for (auto [v, w] : adj[u])
    {
        if (v == parent)
            continue;
        dfs1(v, u, adj, dp, subtree_size);
        subtree_size[u] += subtree_size[v];
        dp[u] += dp[v] + subtree_size[v] * w;
    }
}

void dfs2(int u, int parent, vector<vector<edge>> &adj, vector<long long> &dist,
          vector<int> &subtree_size, int n)
{
    for (auto [v, w] : adj[u])
    {
        if (v == parent)
            continue;
        dist[v] = dist[u] + w * (n - 2 * subtree_size[v]);
        dfs2(v, u, adj, dist, subtree_size, n);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<vector<edge>> adj(n + 1);
    vector<long long> dp(n + 1);
    vector<long long> dist(n + 1);
    vector<int> subtree_size(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    dfs1(1, 0, adj, dp, subtree_size);
    dist[1] = dp[1];
    dfs2(1, 0, adj, dist, subtree_size, n);
    for (int i = 1; i <= n; i++)
        cout << dist[i] << ((i == n) ? "\n" : " ");
    return 0;
}