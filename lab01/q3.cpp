// Find singleton
// Sorted blocks of size k

#include <iostream>
#include <vector>
using namespace std;

int find(const vector<int> &num, int n, int k)
{
    int l = 0;
    int r = n - 1;
    while (l < r)
    {
        int m = l + (r - l) / 2;
        int block = m - (m % k);
        if (block + k - 1 < n && num[block] == num[block + k - 1])
            l = block + k;
        else
            r = block;
    }
    return num[l];
}

int main()
{
    int n, k;
    cin >> n >> k;
    vector<int> num(n);
    for (auto &i : num)
        cin >> i;
    int single = find(num, n, k);
    cout << single << endl;
    return 0;
}