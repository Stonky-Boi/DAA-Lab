// Maximize the size of the subset S of vertices such that the number of edges inside S is at most K

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int nA, nB, m, K;
    cin >> nA >> nB >> m >> K;
    vector<vector<int>> adj(nA);
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adj[u].push_back(v);
    }
    int max_size = 0;
    int total_masks = 1 << nA;
    for (int mask = 0; mask < total_masks; mask++)
    {
        int size_A = 0;
        int temp = mask;
        while (temp > 0)
        {
            temp = temp & (temp - 1);
            size_A++;
        }
        vector<int> deg(nB, 0);
        for (int i = 0; i < nA; i++)
        {
            if ((mask >> i) & 1)
            {
                for (int b : adj[i])
                    deg[b]++;
            }
        }
        sort(deg.begin(), deg.end());
        int used_edges = 0;
        int size_B = 0;
        for (int i = 0; i < nB; i++)
        {
            if (used_edges + deg[i] <= K)
            {
                used_edges += deg[i];
                size_B++;
            }
            else
                break;
        }
        int total_size = size_A + size_B;
        if (total_size > max_size)
            max_size = total_size;
    }
    cout << max_size << endl;
    return 0;
}