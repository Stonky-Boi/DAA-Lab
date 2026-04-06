// For every edge in MST, remove it
// Find minimum replacement cost

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct edge
{
    int to;
    int weight;
    int index;
};

const int INF = numeric_limits<int>::max();

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> graph(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        graph[u].push_back({v, w, i});
        graph[v].push_back({u, w, i});
    }
    vector<bool> in_mst(m, false);
    vector<int> replacement_cost(m, INF);
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> parent_edge(n, -1);
    vector<int> depth(n, 0);
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> min_heap;
    min_heap.push({0, {0, -1}});
    while (!min_heap.empty())
    {
        auto curr = min_heap.top();
        min_heap.pop();
        auto [node, edge_index] = curr.second;
        if (visited[node])
            continue;
        visited[node] = true;
        if (edge_index != -1)
            in_mst[edge_index] = true;
        for (auto e : graph[node])
        {
            if (!visited[e.to])
            {
                parent[e.to] = node;
                parent_edge[e.to] = e.index;
                depth[e.to] = depth[node] + 1;
                min_heap.push({e.weight, {e.to, e.index}});
            }
        }
    }
    for (int u = 0; u < n; u++)
    {
        for (auto [v, w, index] : graph[u])
        {
            if (in_mst[index])
                continue;
            int x = u;
            int y = v;
            while (depth[x] > depth[y])
            {
                int edge_index = parent_edge[x];
                replacement_cost[edge_index] = min(replacement_cost[edge_index], w);
                x = parent[x];
            }
            while (depth[y] > depth[x])
            {
                int edge_index = parent_edge[y];
                replacement_cost[edge_index] = min(replacement_cost[edge_index], w);
                y = parent[y];
            }
            while (x != y)
            {
                int edge_x = parent_edge[x];
                int edge_y = parent_edge[y];
                replacement_cost[edge_x] = min(replacement_cost[edge_x], w);
                replacement_cost[edge_y] = min(replacement_cost[edge_y], w);
                x = parent[x];
                y = parent[y];
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (in_mst[i])
        {
            int cost = replacement_cost[i];
            if (cost == INF)
                cost = -1;
            cout << i + 1 << " " << cost << endl;
        }
    }
    return 0;
}