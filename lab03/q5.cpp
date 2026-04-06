// Find number of binary strings of length n
// No starting 1 and no two consecutive 1s

#include <iostream>
using namespace std;

int count_strings(int n)
{
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    return count_strings(n - 1) + count_strings(n - 2);
}

int main()
{
    int n;
    cin >> n;
    cout << count_strings(n) << endl;
    return 0;
}