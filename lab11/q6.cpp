// Minimize number of safe-mode servers while satisfying all 3-server policies

#include <iostream>
#include <vector>
using namespace std;

void dfs(int index, int used, int n, int m, int &minimum_servers,
         vector<vector<int>> &clauses, vector<int> &assignment, vector<int> &clause_count)
{
    if (used >= minimum_servers)
        return;
    if (index == n)
    {
        for (int i = 0; i < m; i++)
        {
            if (clause_count[i] == 0)
                return;
        }
        minimum_servers = used;
        return;
    }
    assignment[index] = 0;
    dfs(index + 1, used, n, m, minimum_servers, clauses, assignment, clause_count);
    assignment[index] = 1;
    vector<int> affected;
    for (int i = 0; i < m; i++)
    {
        if (clauses[i][0] == index || clauses[i][1] == index || clauses[i][2] == index)
        {
            clause_count[i]++;
            affected.push_back(i);
        }
    }
    bool possible = true;
    for (int i = 0; i < m; i++)
    {
        int cnt_safe = 0;
        bool fully_assigned = true;
        for (int v : clauses[i])
        {
            if (assignment[v] == 1)
                cnt_safe++;
            if (assignment[v] == -1)
                fully_assigned = false;
        }
        if (fully_assigned && cnt_safe == 0)
        {
            possible = false;
            break;
        }
    }
    if (possible)
        dfs(index + 1, used + 1, n, m, minimum_servers, clauses, assignment, clause_count);
    for (int i : affected)
        clause_count[i]--;
    assignment[index] = -1;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> clauses(m, vector<int>(3));
    vector<int> assignment(n, -1);
    vector<int> clause_count(m, 0);
    for (int i = 0; i < m; i++)
    {
        cin >> clauses[i][0] >> clauses[i][1] >> clauses[i][2];
        clauses[i][0]--;
        clauses[i][1]--;
        clauses[i][2]--;
    }
    int minimum_servers = n;
    dfs(0, 0, n, m, minimum_servers, clauses, assignment, clause_count);
    cout << minimum_servers << endl;
    return 0;
}