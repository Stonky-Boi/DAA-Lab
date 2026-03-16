#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct project
{
    int start, finish, profit;
};

bool compare(project a, project b)
{
    return a.finish < b.finish;
}

int binary_search(vector<project> &p, int i)
{
    int l = 0;
    int r = i - 1;
    int last = -1;
    while (l <= r)
    {
        int m = (l + r) / 2;
        if (p[m].finish < p[i].start)
        {
            last = m;
            l = m + 1;
        }
        else
            r = m - 1;
    }
    return last;
}

int main()
{
    int n;
    cin >> n;
    vector<project> p(n);
    for (int i = 0; i < n; i++)
        cin >> p[i].start >> p[i].finish >> p[i].profit;
    sort(p.begin(), p.end(), compare);
    vector<long long> dp(n);
    for (int i = 0; i < n; i++)
    {
        long long take = p[i].profit;
        int last = binary_search(p, i);
        if (last != -1)
            take += dp[last];
        long long skip = (i > 0 ? dp[i - 1] : 0);
        dp[i] = max(take, skip);
    }
    cout << dp[n - 1] << endl;
}