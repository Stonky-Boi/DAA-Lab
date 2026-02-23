// Stable matching with penalty

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> gale_shapley(int n, vector<vector<int>> &a_pref, vector<vector<int>> &s_pref)
{
    vector<vector<int>> s_rank(n, vector<int>(n));
    for (int s = 0; s < n; s++)
        for (int r = 0; r < n; r++)
            s_rank[s][s_pref[s][r]] = r;
    vector<int> a_match(n, -1);
    vector<int> s_optimal(n, -1);
    vector<int> next_proposal(n, 0);
    queue<int> free;
    for (int a = 0; a < n; a++)
        free.push(a);
    while (!free.empty())
    {
        int a = free.front();
        free.pop();
        int s = a_pref[a][next_proposal[a]];
        next_proposal[a]++;
        if (s_optimal[s] == -1)
        {
            s_optimal[s] = a;
            a_match[a] = s;
        }
        else
        {
            int current_a = s_optimal[s];
            if (s_rank[s][a] < s_rank[s][current_a])
            {
                s_optimal[s] = a;
                a_match[a] = s;
                a_match[current_a] = -1;
                free.push(current_a);
            }
            else
                free.push(a);
        }
    }
    return a_match;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> a_pref(n, vector<int>(n));
    vector<vector<int>> s_pref(n, vector<int>(n));
    vector<vector<int>> penalty(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            a_pref[i][j] = x - 1;
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            s_pref[i][j] = x - 1;
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> penalty[i][j];
    vector<int> a_match = gale_shapley(n, a_pref, s_pref);
    long long a_penalty = 0;
    for (int i = 0; i < n; i++)
        a_penalty += penalty[i][a_match[i]];
    vector<int> s_match = gale_shapley(n, s_pref, a_pref);
    long long s_penalty = 0;
    for (int i = 0; i < n; i++)
    {
        int app = s_match[i];
        s_penalty += penalty[app][i];
    }
    cout << min(a_penalty, s_penalty) << endl;
    return 0;
}