// Determine the minimum number of cache misses

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

int main()
{
    long long n, k, w;
    cin >> n >> k >> w;
    vector<long long> requests(n);
    for (int i = 0; i < n; i++)
        cin >> requests[i];
    if (k == 0)
    {
        cout << n << endl;
        return 0;
    }
    map<long long, queue<int>> future_positions;
    for (int i = 0; i < n; i++)
        future_positions[requests[i]].push(i);
    set<pair<long long, long long>> cache_order; // (next_use_position, page)
    set<long long> cache;
    long long misses = 0;
    for (int i = 0; i < n; i++)
    {
        long long page = requests[i];
        future_positions[page].pop();
        long long next_use = n + 1;
        if (!future_positions[page].empty())
            next_use = future_positions[page].front();
        if (next_use > i + w)
            next_use = n + 1;
        if (cache.count(page))
        {
            cache_order.erase({next_use, page});
            cache_order.insert({next_use, page});
            continue;
        }
        misses++;
        if ((long long)cache.size() == k)
        {
            auto last_element = *cache_order.rbegin();
            long long evict_page = last_element.second;
            cache.erase(evict_page);
            cache_order.erase(last_element);
        }
        cache.insert(page);
        cache_order.insert({next_use, page});
    }
    cout << misses << endl;
    return 0;
}