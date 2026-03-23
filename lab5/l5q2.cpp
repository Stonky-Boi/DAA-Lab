// Multiply two n-digit non-negative integers in O(n^log(2)(3)) time

#include <iostream>
#include <algorithm>
using namespace std;

string remove_zeroes(string s)
{
    size_t position = s.find_first_not_of('0');
    if (position == string::npos)
        return "0";
    return s.substr(position);
}

string add(string a, string b)
{
    string result = "";
    int carry = 0;
    int n = max(a.size(), b.size());
    for (int i = 0; i < n; ++i)
    {
        int x = i < a.size() ? a[a.size() - 1 - i] - '0' : 0;
        int y = i < b.size() ? b[b.size() - 1 - i] - '0' : 0;
        int sum = x + y + carry;
        result += (sum % 10) + '0';
        carry = sum / 10;
    }
    if (carry)
        result += carry + '0';
    reverse(result.begin(), result.end());
    return remove_zeroes(result);
}

string subtract(string a, string b)
{
    string result = "";
    int borrow = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        int x = a[a.size() - 1 - i] - '0';
        int y = i < b.size() ? b[b.size() - 1 - i] - '0' : 0;
        int difference = x - y - borrow;
        if (difference < 0)
        {
            difference += 10;
            borrow = 1;
        }
        else
            borrow = 0;
        result += difference + '0';
    }
    reverse(result.begin(), result.end());
    return remove_zeroes(result);
}

string power_10(string a, int k)
{
    if (a == "0")
        return "0";
    string result = a;
    result.append(k, '0');
    return result;
}

string multiply(string x, string y)
{
    int n = max(x.size(), y.size());
    if (n == 1)
    {
        int product = (x[0] - '0') * (y[0] - '0');
        return to_string(product);
    }
    int m = n / 2;
    string x1 = x.substr(0, x.size() - m);
    string x0 = x.substr(x.size() - m);
    string y1 = y.substr(0, y.size() - m);
    string y0 = y.substr(y.size() - m);
    string z2 = multiply(x1, y1);
    string z0 = multiply(x0, y0);
    string z1 = multiply(add(x1, x0), add(y1, y0));
    z1 = subtract(subtract(z1, z2), z0);
    string result = add(add(power_10(z2, 2 * m), power_10(z1, m)), z0);
    return remove_zeroes(result);
}

int main()
{
    int n;
    cin >> n;
    string a, b;
    cin >> a >> b;
    cout << multiply(a, b) << endl;
    return 0;
}