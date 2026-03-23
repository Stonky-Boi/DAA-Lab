// Find the minimum number of coins required to make the exact sum S

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

int main()
{
    int n, s;
    cin >> n >> s;
    vector<int> value(n);
    for (auto &coin : value)
        cin >> coin;
    vector<int> dp(s + 1, INF);
    dp[0] = 0;
    for (int curr_sum = 1; curr_sum <= s; curr_sum++)
        for (auto coin : value)
            if (curr_sum >= coin && dp[curr_sum - coin] != INF)
                dp[curr_sum] = min(dp[curr_sum], dp[curr_sum - coin] + 1);
    if (dp[s] == INF)
        cout << -1 << endl;
    else
        cout << dp[s] << endl;
    return 0;
}