#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void dfs(int node, int parent, vector<vector<int>> &graph,
         vector<long long> &dp_take, vector<long long> &dp_skip)
{
    dp_take[node] = 1;
    dp_skip[node] = 0;
    for (int next : graph[node])
    {
        if (next == parent)
            continue;
        dfs(next, node, graph, dp_take, dp_skip);
        dp_take[node] += dp_skip[next];
        dp_skip[node] += max(dp_take[next], dp_skip[next]);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    vector<long long> dp_take(n + 1), dp_skip(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1, 0, graph, dp_take, dp_skip);
    cout << max(dp_take[1], dp_skip[1]) << endl;
}