// Each node has an associated value, which can be positive or negative and a weight
// Choose a path starting from node 1 to any node to maximise the total profit

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void dfs(int node, int parent, int depth, int parity,
         long long even_sum, long long odd_sum, long long &max_profit,
         const vector<vector<pair<int, long long>>> &adj, const vector<long long> &a)
{
    if (depth % 2 == 0)
        even_sum += a[node];
    else
        odd_sum += a[node];
    long long current_profit;
    if (parity == 0)
        current_profit = even_sum;
    else
        current_profit = odd_sum;
    if (current_profit > max_profit)
        max_profit = current_profit;
    for (auto [neighbor, weight] : adj[node])
    {
        if (neighbor == parent)
            continue;
        int new_parity = (parity + (weight % 2)) % 2;
        dfs(neighbor, node, depth + 1, new_parity, even_sum, odd_sum, max_profit, adj, a);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<long long> a(n);
    for (long long &i : a)
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
    long long max_profit = LLONG_MIN;
    dfs(0, -1, 1, 0, 0, 0, max_profit, adj, a);
    cout << max_profit << endl;
    return 0;
}