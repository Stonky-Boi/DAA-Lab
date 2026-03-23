// You can climb either 1 or 2 steps to the next level
// Reach the top with the minimum possible total cost

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> cost(n);
    for (auto &value : cost)
        cin >> value;
    // vector<int> dp(n);
    // dp[0] = cost[0];
    // dp[1] = cost[1];
    int prev2 = cost[0];
    int prev1 = cost[1];
    for (int i = 2; i < n; i++)
    {
        // dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
        int curr = cost[i] + min(prev1, prev2);
        prev2 = prev1;
        prev1 = curr;
    }
    // int result = min(dp[n - 1], dp[n - 2]);
    int result = min(prev1, prev2);
    cout << result << endl;
    return 0;
}