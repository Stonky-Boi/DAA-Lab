// Determine the maximum value obtained by parenthesizing the given expression

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main()
{
    string s;
    cin >> s;
    vector<long long> numbers;
    vector<char> operations;
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s[i]))
        {
            long long d = 0;
            while (i < s.size() && isdigit(s[i]))
            {
                d = d * 10 + (s[i] - '0');
                i++;
            }
            numbers.push_back(d);
            i--;
        }
        else
            operations.push_back(s[i]);
    }
    int n = numbers.size();
    vector<vector<long long>> dp_max(n, vector<long long>(n, 0)), dp_min(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++)
        dp_max[i][i] = dp_min[i][i] = numbers[i];
    for (int l = 2; l <= n; l++)
    {
        for (int i = 0; i + l - 1 < n; i++)
        {
            int j = i + l - 1;
            dp_max[i][j] = numeric_limits<long long>::min();
            dp_min[i][j] = numeric_limits<long long>::max();
            for (int k = i; k < j; k++)
            {
                char op = operations[k];
                long long a = dp_max[i][k], b = dp_min[i][k], c = dp_max[k + 1][j], d = dp_min[k + 1][j];
                vector<long long> values;
                switch (op)
                {
                case '+':
                    values = {a + c, a + d, b + c, b + d};
                    break;
                case '-':
                    values = {a - c, a - d, b - c, b - d};
                    break;
                case '*':
                    values = {a * c, a * d, b * c, b * d};
                    break;
                default:
                    break;
                }
                for (long long v : values)
                {
                    if (v > dp_max[i][j])
                        dp_max[i][j] = v;
                    if (v < dp_min[i][j])
                        dp_min[i][j] = v;
                }
            }
        }
    }
    cout << dp_max[0][n - 1] << endl;
    return 0;
}