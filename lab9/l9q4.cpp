#include <iostream>
#include <vector>
using namespace std;

struct edge
{
    int to;
    long long weight;
};

void dfs(int u, int parent, vector<vector<edge>> &adj, vector<long long> &dp_take, vector<long long> &dp_skip)
{
    long long sum = 0;
    for (auto [v, w] : adj[u])
    {
        if (v == parent)
            continue;
        dfs(v, u, adj, dp_take, dp_skip);
        sum += max(dp_take[v], dp_skip[v]);
    }
    dp_skip[u] = sum;
    dp_take[u] = sum;
    for (auto [v, w] : adj[u])
    {
        if (v == parent)
            continue;
        long long value = sum - max(dp_take[v], dp_skip[v]) + dp_skip[v] + w;
        if (value > dp_take[u])
            dp_take[u] = value;
    }
}

int main()
{
    int n;
    cin >> n;
    vector<vector<edge>> adj(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<long long> dp_take(n + 1, 0), dp_skip(n + 1, 0);
    dfs(1, 0, adj, dp_take, dp_skip);
    cout << max(dp_take[1], dp_skip[1]) << endl;
    return 0;
}