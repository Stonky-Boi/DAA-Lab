// You can climb 1 or 2 steps at a time
// 2 steps cannot be consecutive
// Find number of ways to climb N stairs

#include <iostream>
using namespace std;

int count_ways(int n)
{
    if (n == 0 || n == 1)
        return 1;
    if (n == 2)
        return 2;
    return count_ways(n - 1) + count_ways(n - 3);
}

int main()
{
    int n;
    cin >> n;
    cout << count_ways(n) << endl;
    return 0;
}