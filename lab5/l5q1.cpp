// Second closest pair

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long square_distance(pair<long long, long long> a, pair<long long, long long> b)
{
    long long delta_x = a.first - b.first;
    long long delta_y = a.second - b.second;
    return delta_x * delta_x + delta_y * delta_y;
}

bool compare_x(pair<long long, long long> a, pair<long long, long long> b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

bool compare_y(pair<long long, long long> a, pair<long long, long long> b)
{
    if (a.second == b.second)
        return a.first < b.first;
    return a.second < b.second;
}

pair<long long, long long> closest_pair(pair<long long, long long> points[], int l, int r, pair<long long, long long> temp[])
{
    if (r - l <= 3)
    {
        long long d1 = 1e18, d2 = 1e18;
        for (int i = l; i < r; i++)
            for (int j = i + 1; j < r; j++)
            {
                long long d = square_distance(points[i], points[j]);
                if (d < d1)
                {
                    d2 = d1;
                    d1 = d;
                }
                else if (d != d1 && d < d2)
                    d2 = d;
            }
        sort(points + l, points + r, compare_y);
        return {d1, d2};
    }
    int m = (l + r) / 2;
    long long mid_x = points[m].first;
    auto left = closest_pair(points, l, m, temp);
    auto right = closest_pair(points, m, r, temp);
    int index = 0, i = l, j = m;
    while (i < m && j < r)
    {
        if (points[i].second < points[j].second)
            temp[index++] = points[i++];
        else
            temp[index++] = points[j++];
    }
    while (i < m)
        temp[index++] = points[i++];
    while (j < r)
        temp[index++] = points[j++];
    for (i = 0; i < index; i++)
        points[l + i] = temp[i];
    vector<long long> candidates = {left.first, left.second, right.first, right.second};
    sort(candidates.begin(), candidates.end());
    long long delta1 = candidates[0], delta2 = 1e18;
    for (int k = 1; k < 4; k++)
    {
        if (candidates[k] != delta1)
        {
            delta2 = candidates[k];
            break;
        }
    }
    vector<int> strip;
    for (i = l; i < r; i++)
        if ((points[i].first - mid_x) * (points[i].first - mid_x) <= delta2)
            strip.push_back(i);
    for (i = 0; i < strip.size(); i++)
        for (int j = i + 1; j < strip.size() && (points[strip[j]].second - points[strip[i]].second) * (points[strip[j]].second - points[strip[i]].second) <= delta2; j++)
        {
            long long d = square_distance(points[strip[i]], points[strip[j]]);
            if (d < delta1)
            {
                delta2 = delta1;
                delta1 = d;
            }
            else if (d != delta1 && d < delta2)
                delta2 = d;
        }
    return {delta1, delta2};
}

int main()
{
    int n;
    cin >> n;
    pair<long long, long long> points[n], temp[n];
    for (auto &[x, y] : points)
        cin >> x >> y;
    sort(points, points + n, compare_x);
    auto result = closest_pair(points, 0, n, temp);
    if (result.second == 1e18)
        cout << -1 << endl;
    else
    {
        cout << fixed;
        cout.precision(6);
        cout << sqrt((double)result.second) << endl;
    }
}