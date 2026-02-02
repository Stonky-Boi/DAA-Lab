// Count inversions in O(nlogn) time

#include <iostream>
using namespace std;

int count_inverted(int arr[], int n)
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
    int l_count = count_inverted(l, m);
    int r_count = count_inverted(r, n - m);
    int i = 0, j = 0, k = 0, count = 0;
    while (i < m && j < n - m)
    {
        if (l[i] <= r[j])
            arr[k++] = l[i++];
        else
        {
            arr[k++] = r[j++];
            count += (m - i);
        }
    }
    while (i < m)
        arr[k++] = l[i++];
    while (j < n - m)
        arr[k++] = r[j++];
    return l_count + r_count + count;
}

int main()
{
    int n;
    cin >> n;
    int a[n];
    for (auto &i : a)
        cin >> i;
    int inversions = count_inverted(a, n);
    cout << inversions << endl;
    return 0;
}