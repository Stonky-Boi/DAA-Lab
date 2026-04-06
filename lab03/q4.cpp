// You can climb 1 or 2 steps at a time
// Find number of ways to climb N stairs

#include <iostream>
using namespace std;

int count_ways(int n)
{
    if (n <= 1)
        return 1;
    return count_ways(n - 1) + count_ways(n - 2);
}

int main()
{
    int n;
    cin >> n;
    cout << count_ways(n) << endl;
    return 0;
}