// Find misplaced element and fix it

#include <iostream>
#include <vector>
using namespace std;

int find(const vector<int> &num, int n)
{
    for (int i = 0; i < n - 1; i++)
        if (num[i] > num[i + 1])
            return i;
    return -1;
}

int position(const vector<int> &num, int n, int value)
{
    int l = 0;
    int r = n;
    while (l < r)
    {
        int m = l + (r - l) / 2;
        if (num[m] < value)
            l = m + 1;
        else
            r = m;
    }
    return l;
}

int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    for (auto &i : num)
        cin >> i;
    int index = find(num, n);
    int value = num[index];
    num.erase(num.begin() + index);
    int correct = position(num, n, value);
    num.insert(num.begin() + correct, value);
    cout << "Misplaced index: " << index << endl;
    cout << "Corrected num: [ ";
    for (int i : num)
        cout << i << " ";
    cout << "]" << endl;
    return 0;
}