// Calculate the total number of distinct ways to tile
// a rectangular floor of size N x M using dominos of size 2 x 1 or 1 x 2

#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1000000007;

void generate_next_masks(int curr_mask, int position, int next_mask, int m, vector<int> &result)
{
    if (position == m)
    {
        result.push_back(next_mask);
        return;
    }
    if (curr_mask & (1 << position))
        generate_next_masks(curr_mask, position + 1, next_mask, m, result);
    else
    {
        generate_next_masks(curr_mask, position + 1, next_mask | (1 << position), m, result);
        if (position + 1 < m && !(curr_mask & (1 << (position + 1))))
            generate_next_masks(curr_mask, position + 2, next_mask, m, result);
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    if ((n * m) % 2 != 0)
    {
        cout << 0 << endl;
        return 0;
    }
    int max_mask = 1 << m;
    vector<vector<int>> dp(n + 1, vector<int>(max_mask, 0));
    dp[0][0] = 1;
    for (int row = 0; row < n; row++)
        for (int mask = 0; mask < max_mask; mask++)
        {
            if (dp[row][mask] == 0)
                continue;
            vector<int> next_masks;
            generate_next_masks(mask, 0, 0, m, next_masks);
            for (auto next_mask : next_masks)
                dp[row + 1][next_mask] = (dp[row + 1][next_mask] + dp[row][mask]) % MOD;
        }
    cout << dp[n][0] << endl;
    return 0;
}