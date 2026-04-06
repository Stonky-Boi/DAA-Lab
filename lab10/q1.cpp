// Determine if the given 4-SAT formula is satisfiable

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct clause
{
    int a, b, c, d;
};

int n, m;
vector<clause> clauses;
vector<int> assignment;
// 0 unassigned, 1 true, -1 false

bool satisfied(const clause &cl)
{
    int literals[4] = {cl.a, cl.b, cl.c, cl.d};
    for (int i = 0; i < 4; i++)
    {
        int l = literals[i];
        int variable = abs(l);
        if (assignment[variable] == 0)
            continue;
        if ((l > 0 && assignment[variable] == 1) || (l < 0 && assignment[variable] == -1))
            return true;
    }
    return false;
}

bool unit_propagate(vector<int> &changed)
{
    bool updated = true;
    while (updated)
    {
        updated = false;
        for (auto cl : clauses)
        {
            if (satisfied(cl))
                continue;
            int unassigned = 0, count = 0;
            int literals[4] = {cl.a, cl.b, cl.c, cl.d};
            for (int i = 0; i < 4; i++)
            {
                int variable = abs(literals[i]);
                if (assignment[variable] == 0)
                {
                    count++;
                    unassigned = literals[i];
                }
            }
            if (count == 1)
            {
                int variable = abs(unassigned);
                int value = (unassigned > 0 ? 1 : -1);
                if (assignment[variable] == 0)
                {
                    assignment[variable] = value;
                    changed.push_back(variable);
                    updated = true;
                }
            }
            else if (count == 0)
                return false;
        }
    }
    return true;
}

bool solve()
{
    vector<int> changed;
    if (!unit_propagate(changed))
    {
        for (auto x : changed)
            assignment[x] = 0;
        return false;
    }
    int variable = -1;
    for (int i = 1; i <= n; i++)
    {
        if (assignment[i] == 0)
        {
            variable = i;
            break;
        }
    }
    if (variable == -1)
        return true;
    assignment[variable] = 1;
    if (solve())
        return true;
    assignment[variable] = -1;
    if (solve())
        return true;
    assignment[variable] = 0;
    for (auto x : changed)
        assignment[x] = 0;
    return false;
}

int main()
{
    cin >> n >> m;
    clauses.resize(m);
    for (auto &cl : clauses)
        cin >> cl.a >> cl.b >> cl.c >> cl.d;
    assignment.assign(n + 1, 0);
    if (solve())
    {
        cout << "YES" << endl;
        for (int i = 1; i <= n; i++)
            cout << ((assignment[i] == 1) ? i : -i) << ((i == n) ? "\n" : " ");
        cout << endl;
    }
    else
        cout << "NO" << endl;
    return 0;
}