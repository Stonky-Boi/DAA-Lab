// Count inversions in O(nlogn)
// i<j, A[i]>A[j] and j-i<=k

#include <iostream>
using namespace std;

int count_inverted(int arr[], int n, int k)
{
    if (n <= 1)
        return 0;
    int m = n / 2;
    int l[m];
    int r[n - m];
    for (int i = 0; i < m; i++)
        l[i] = arr[i];
    for (int i = m; i < n; i++)
        r[i - m] = arr[i];
    int l_count = count_inverted(l, m, k);
    int r_count = count_inverted(r, n - m, k);
    int i = 0, j = 0;
    int k_idx = 0, count = 0;
    for (i = 0; i < m; i++)
        while (j < n - m && r[j] < l[i] && (j + m - i) <= k)
        {
            count++;
            j++;
        }
    i = 0;
    j = 0;
    k_idx = 0;
    while (i < m && j < n - m)
    {
        if (l[i] <= r[j])
            arr[k_idx++] = l[i++];
        else
            arr[k_idx++] = r[j++];
    }
    while (i < m)
        arr[k_idx++] = l[i++];
    while (j < n - m)
        arr[k_idx++] = r[j++];
    return l_count + r_count + count;
}

int main()
{
    int n, k;
    cin >> n >> k;
    int a[n];
    for (auto &i : a)
        cin >> i;
    int inversions = count_inverted(a, n, k);
    cout << inversions << endl;
    return 0;
}