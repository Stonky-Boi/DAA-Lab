// Determine the minimum total search cost

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> f(n);
    for (int i = 0; i < n; i++)
        cin >> f[i];
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; i++)
        prefix[i + 1] = prefix[i] + f[i];
    vector<vector<long long>> dp(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        dp[i][i] = f[i];
    for (int l = 2; l <= n; l++)
    {
        for (int i = 0; i + l - 1 < n; i++)
        {
            int j = i + l - 1;
            dp[i][j] = numeric_limits<long long>::max();
            long long total_freq = prefix[j + 1] - prefix[i];
            for (int r = i; r <= j; r++)
            {
                long long left_cost = (r > i) ? dp[i][r - 1] : 0;
                long long right_cost = (r < j) ? dp[r + 1][j] : 0;
                long long cost = left_cost + right_cost + total_freq;
                if (cost < dp[i][j])
                    dp[i][j] = cost;
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    return 0;
}