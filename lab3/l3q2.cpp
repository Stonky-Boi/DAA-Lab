// Find maximum possible sum of any contiguous subarray in O(nlogn)

#include <iostream>
#include <climits>
using namespace std;

int maximum_subarray(int arr[], int l, int r)
{
    if (l == r)
        return arr[l];
    int m = l + (r - l) / 2;
    int l_max = maximum_subarray(arr, l, m);
    int r_max = maximum_subarray(arr, m + 1, r);
    int l_sum = 0, max_l = INT_MIN;
    for (int i = m; i >= l; i--)
    {
        l_sum += arr[i];
        max_l = max(max_l, l_sum);
    }
    int r_sum = 0, max_r = INT_MIN;
    for (int i = m + 1; i <= r; i++)
    {
        r_sum += arr[i];
        max_r = max(max_r, r_sum);
    }
    return max(max(l_max, r_max), max_l + max_r);
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (auto &i : a)
        cin >> i;
    int max_sum = maximum_subarray(a, 0, n - 1);
    cout << max_sum << endl;
    return 0;
}