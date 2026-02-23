// Interval scheduling

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct job
{
    long long time;
    long long deadline;
};

bool compare(job &a1, job &a2)
{
    if (a1.deadline == a2.deadline)
        return a1.time < a2.time;
    return a1.deadline < a2.deadline;
}

int main()
{
    int n, w;
    cin >> n >> w;
    vector<job> tasks(n);
    for (int i = 0; i < n; i++)
        cin >> tasks[i].time >> tasks[i].deadline;
    sort(tasks.begin(), tasks.end(), compare);
    priority_queue<long long, vector<long long>, greater<long long>> workers;
    for (int i = 0; i < w; i++)
        workers.push(0);
    long long max_lateness = 0;
    long long max_load = 0;
    for (auto t : tasks)
    {
        long long curr_load = workers.top();
        workers.pop();
        long long completion_time = curr_load + t.time;
        long long lateness = max(0LL, completion_time - t.deadline);
        max_lateness = max(max_lateness, lateness);
        max_load = max(max_load, completion_time);
        workers.push(completion_time);
    }
    cout << max(max_lateness, max_load) << endl;
    return 0;
}