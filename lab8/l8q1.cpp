// A road is secured if at least one city has a sentinel stationed in it
// Find the minimum total cost to secure each road

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int node, int parent, vector<vector<int>> &graph, vector<long long> &cost,
         vector<long long> &dp_take, vector<long long> &dp_skip)
{
    dp_take[node] = cost[node];
    dp_skip[node] = 0;
    for (auto next : graph[node])
    {
        if (next == parent)
            continue;
        dfs(next, node, graph, cost, dp_take, dp_skip);
        dp_take[node] += min(dp_take[next], dp_skip[next]);
        dp_skip[node] += dp_take[next];
    }
}

int main()
{
    int n;
    cin >> n;
    vector<long long> c(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<long long> dp_take(n + 1), dp_skip(n + 1);
    dfs(1, 0, graph, c, dp_take, dp_skip);
    cout << min(dp_take[1], dp_skip[1]) << endl;
    return 0;
}