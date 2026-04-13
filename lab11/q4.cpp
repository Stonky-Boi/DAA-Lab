// Minimize the total cost = (sum of MST edge weights) + (minimum vertex cover cost on the MST)

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct edge
{
    long long weight;
    int node;
    int parent;
    bool operator>(const edge &other) const
    {
        return weight > other.weight;
    }
};

void dfs(int node, int parent, const vector<vector<int>> &tree, const vector<long long> &cost,
         vector<long long> &dp_take, vector<long long> &dp_skip)
{
    dp_take[node] = cost[node];
    dp_skip[node] = 0;
    for (int neighbor : tree[node])
    {
        if (neighbor == parent)
            continue;
        dfs(neighbor, node, tree, cost, dp_take, dp_skip);
        dp_skip[node] += dp_take[neighbor];
        long long best_child = min(dp_take[neighbor], dp_skip[neighbor]);
        dp_take[node] += best_child;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> adj(n);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<bool> visited(n, false);
    vector<vector<int>> tree(n);
    priority_queue<edge, vector<edge>, greater<edge>> pq;
    pq.push({0, 0, -1});
    long long mst_cost = 0;
    while (!pq.empty())
    {
        auto [weight, node, parent] = pq.top();
        pq.pop();
        if (visited[node])
            continue;
        visited[node] = true;
        mst_cost += weight;
        if (parent != -1)
        {
            tree[node].push_back(parent);
            tree[parent].push_back(node);
        }
        for (auto [neighbor, w] : adj[node])
            if (!visited[neighbor])
                pq.push({w, neighbor, node});
    }
    vector<long long> cost(n);
    for (long long &c : cost)
        cin >> c;
    vector<long long> dp_take(n, 0), dp_skip(n, 0);
    dfs(0, -1, tree, cost, dp_take, dp_skip);
    long long vertex_cover_cost = min(dp_take[0], dp_skip[0]);
    cout << mst_cost + vertex_cover_cost << endl;
    return 0;
}