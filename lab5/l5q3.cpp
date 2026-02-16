// Maximum overlap

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(pair<long long, int> a, pair<long long, int> b)
{
    if (a.first == b.first)
        return a.second < b.second;
    return a.first < b.first;
}

int main()
{
    int n;
    cin >> n;
    vector<pair<long long, int>> events;
    for (int i = 0; i < n; i++)
    {
        long long start, end;
        cin >> start >> end;
        events.push_back({start, 1});
        events.push_back({end, -1});
    }
    sort(events.begin(), events.end(), compare);
    long long count = 0;
    long long machines = 0;
    for (auto e : events)
    {
        count += e.second;
        if (count > machines)
            machines = count;
    }
    cout << machines << endl;
    return 0;
}