// Remove as many highcost edges as possible
// without disconnecting the graph

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    long long total_cost = 0;
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        total_cost += w;
    }
    vector<bool> visited(n, false);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min_heap;
    long long mst_cost = 0;
    int visited_count = 0;
    min_heap.push({0, 0});
    while (!min_heap.empty() && visited_count < n)
    {
        auto [cost, node] = min_heap.top();
        min_heap.pop();
        if (visited[node])
            continue;
        visited[node] = true;
        mst_cost += cost;
        visited_count++;
        for (auto [neighbor, edge_cost] : adj[node])
            if (!visited[neighbor])
                min_heap.push({edge_cost, neighbor});
    }
    long long max_cost = total_cost - mst_cost;
    cout << max_cost << endl;
    return 0;
}