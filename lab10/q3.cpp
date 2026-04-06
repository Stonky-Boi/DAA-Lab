// Compute the minimum total cost to remove vertices and resolve all conflicts

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void solve(int edge_index, int m, const vector<pair<int, int>> &edges, const vector<int> &cost,
           vector<bool> &removed, int curr_cost, int &min_cost)
{
    if (curr_cost >= min_cost)
        return;
    while (edge_index < m)
    {
        auto [u, v] = edges[edge_index];
        if (removed[u] || removed[v])
            edge_index++;
        else
            break;
    }
    if (edge_index == m)
    {
        min_cost = min(min_cost, curr_cost);
        return;
    }
    auto [u, v] = edges[edge_index];
    if (!removed[u])
    {
        removed[u] = true;
        solve(edge_index + 1, m, edges, cost, removed, curr_cost + cost[u], min_cost);
        removed[u] = false;
    }
    if (!removed[v])
    {
        removed[v] = true;
        solve(edge_index + 1, m, edges, cost, removed, curr_cost + cost[v], min_cost);
        removed[v] = false;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> cost(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> cost[i];
    vector<pair<int, int>> edges(m);
    for (auto &[u, v] : edges)
        cin >> u >> v;
    vector<bool> removed(n + 1, false);
    int min_cost = INT_MAX;
    solve(0, m, edges, cost, removed, 0, min_cost);
    cout << min_cost << endl;
    return 0;
}