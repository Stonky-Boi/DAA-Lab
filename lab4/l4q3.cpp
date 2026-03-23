// Find a stable matching between students and companies

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> s_pref(n, vector<int>(n));
    vector<vector<int>> c_pref(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> s_pref[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> c_pref[i][j];
    vector<vector<int>> c_rank(n, vector<int>(n));
    for (int c = 0; c < n; c++)
        for (int r = 0; r < n; r++)
            c_rank[c][c_pref[c][r]] = r;
    vector<int> s_match(n, -1);
    vector<int> c_match(n, -1);
    vector<int> next_proposal(n, 0);
    queue<int> free_students;
    for (int s = 0; s < n; s++)
        free_students.push(s);
    while (!free_students.empty())
    {
        int s = free_students.front();
        free_students.pop();
        int c = s_pref[s][next_proposal[s]];
        next_proposal[s]++;
        if (c_match[c] == -1)
        {
            c_match[c] = s;
            s_match[s] = c;
        }
        else
        {
            int current_s = c_match[c];
            if (c_rank[c][s] < c_rank[c][current_s])
            {
                c_match[c] = s;
                s_match[s] = c;
                s_match[current_s] = -1;
                free_students.push(current_s);
            }
            else
                free_students.push(s);
        }
    }
    for (int s = 0; s < n; s++)
        cout << s << " " << s_match[s] << endl;
    return 0;
}