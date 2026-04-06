// Find a clique whose total weight is maximum

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void solve(int index, int n, const vector<int> &weight, const vector<vector<bool>> &adj,
           vector<int> &clique, int curr_weight, int &max_weight)
{
    if (index > n)
    {
        max_weight = max(max_weight, curr_weight);
        return;
    }
    int remaining = 0;
    for (int i = index; i <= n; i++)
        remaining += weight[i];
    if (curr_weight + remaining <= max_weight)
        return;
    bool possible = true;
    for (auto v : clique)
    {
        if (!adj[v][index])
        {
            possible = false;
            break;
        }
    }
    if (possible)
    {
        clique.push_back(index);
        solve(index + 1, n, weight, adj, clique, curr_weight + weight[index], max_weight);
        clique.pop_back();
    }
    solve(index + 1, n, weight, adj, clique, curr_weight, max_weight);
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> weight(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> weight[i];
    vector<vector<bool>> adj(n + 1, vector<bool>(n + 1, false));
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u][v] = adj[v][u] = true;
    }
    vector<int> clique;
    int max_weight = 0;
    solve(1, n, weight, adj, clique, 0, max_weight);
    cout << max_weight << endl;
    return 0;
}