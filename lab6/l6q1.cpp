// Closest pair between overlapping active drones

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct drone
{
    long long x;
    long long y;
    long long start;
    long long end;
};

long long square_distance(const drone &a, const drone &b)
{
    long long delta_x = a.x - b.x;
    long long delta_y = a.y - b.y;
    return delta_x * delta_x + delta_y * delta_y;
}

bool intervals_overlap(const drone &a, const drone &b)
{
    return max(a.start, b.start) <= min(a.end, b.end);
}

bool compare_x(const drone &a, const drone &b)
{
    if (a.x == b.x)
        return a.y < b.y;
    return a.x < b.x;
}

bool compare_y(const drone &a, const drone &b)
{
    if (a.y == b.y)
        return a.x < b.x;
    return a.y < b.y;
}

long long closest_pair(drone points[], int l, int r, drone temp[])
{
    if (r - l <= 3)
    {
        long long min_distance = 1e18;
        for (int i = l; i < r; i++)
            for (int j = i + 1; j < r; j++)
                if (intervals_overlap(points[i], points[j]))
                {
                    long long d = square_distance(points[i], points[j]);
                    if (d < min_distance)
                        min_distance = d;
                }
        sort(points + l, points + r, compare_y);
        return min_distance;
    }
    int m = (l + r) / 2;
    long long mid_x = points[m].x;
    long long left = closest_pair(points, l, m, temp);
    long long right = closest_pair(points, m, r, temp);
    long long delta = min(left, right);
    int index = 0;
    int i = l;
    int j = m;
    while (i < m && j < r)
    {
        if (points[i].y < points[j].y)
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
    vector<int> strip;
    for (i = l; i < r; i++)
        if ((points[i].x - mid_x) * (points[i].x - mid_x) <= delta)
            strip.push_back(i);
    for (i = 0; i < strip.size(); i++)
        for (int j = i + 1; j < strip.size() && (points[strip[j]].y - points[strip[i]].y) * (points[strip[j]].y - points[strip[i]].y) <= delta; j++)
            if (intervals_overlap(points[strip[i]], points[strip[j]]))
            {
                long long d = square_distance(points[strip[i]], points[strip[j]]);
                if (d < delta)
                    delta = d;
            }
    return delta;
}

int main()
{
    int n;
    cin >> n;
    drone points[n];
    drone temp[n];
    for (int i = 0; i < n; i++)
        cin >> points[i].x >> points[i].y >> points[i].start >> points[i].end;
    sort(points, points + n, compare_x);
    long long result = closest_pair(points, 0, n, temp);
    if (result == 1e18)
        cout << -1 << endl;
    else
    {
        cout << fixed;
        cout.precision(6);
        cout << sqrt((double)result) << endl;
    }
    return 0;
}