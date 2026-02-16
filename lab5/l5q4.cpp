// Stable matching with contentions

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> gale_shapley(int n, vector<vector<int>> &a_pref, vector<vector<int>> &b_pref)
{
    vector<vector<int>> b_rank(n, vector<int>(n));
    for (int b = 0; b < n; b++)
        for (int r = 0; r < n; r++)
            b_rank[b][b_pref[b][r]] = r;
    vector<int> a_match(n, -1);
    vector<int> b_match(n, -1);
    vector<int> next_proposal(n, 0);
    queue<int> free;
    for (int a = 0; a < n; a++)
        free.push(a);
    while (!free.empty())
    {
        int a = free.front();
        free.pop();
        int b = a_pref[a][next_proposal[a]];
        next_proposal[a]++;
        if (b_match[b] == -1)
        {
            b_match[b] = a;
            a_match[a] = b;
        }
        else
        {
            int current_a = b_match[b];
            if (b_rank[b][a] < b_rank[b][current_a])
            {
                b_match[b] = a;
                a_match[a] = b;
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
    vector<vector<int>> b_pref(n, vector<int>(n));
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
            b_pref[i][j] = x - 1;
        }
    vector<int> original_match = gale_shapley(n, a_pref, b_pref);
    int m;
    cin >> m;
    while (m--)
    {
        char letter;
        int index;
        cin >> letter >> index;
        index--;
        vector<vector<int>> a_copy = a_pref;
        vector<vector<int>> b_copy = b_pref;
        for (int j = 0; j < n; j++)
        {
            int x;
            cin >> x;
            x--;
            if (letter == 'A')
                a_copy[index][j] = x;
            else
                b_copy[index][j] = x;
        }
        vector<int> new_match = gale_shapley(n, a_copy, b_copy);
        if (new_match == original_match)
            cout << "TRUTH" << endl;
        else
            cout << "LIE" << endl;
    }
    return 0;
}