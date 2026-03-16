#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<double> a(n);
    for (auto &i : a)
        cin >> i;
    double ans = a[0];
    // vector<double> dp_max(n), dp_min(n);
    // dp_max[0] = a[0];
    // dp_min[0] = a[0];
    double max_prod = a[0], min_prod = a[0];
    for (int i = 1; i < n; i++)
    {
        //     dp_max[i] = max({a[i], a[i] * dp_max[i - 1], a[i] * dp_min[i - 1]});
        //     dp_min[i] = min({a[i], a[i] * dp_max[i - 1], a[i] * dp_min[i - 1]});
        //     ans = max(ans, dp_max[i]);
        double new_max = max({a[i], a[i] * max_prod, a[i] * min_prod});
        double new_min = min({a[i], a[i] * max_prod, a[i] * min_prod});
        max_prod = new_max;
        min_prod = new_min;
        ans = max(ans, max_prod);
    }
    cout << max(1.0, ans) << endl;
}