// You may choose unlimited copies of each item type
// Determine the maximum total value that can be obtained

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, w;
    cin >> n >> w;
    vector<pair<int, int>> item(n);
    for (auto &[weight, value] : item)
        cin >> weight >> value;
    vector<long long> dp(w + 1, 0);
    for (auto [curr_w, curr_v] : item)
        for (int i = curr_w; i <= w; i++)
            dp[i] = max(dp[i], dp[i - curr_w] + curr_v);
    cout << dp[w] << endl;
    return 0;
}