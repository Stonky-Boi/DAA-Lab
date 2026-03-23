// Select the maximum number of activities such that no two selected activities overlap

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct job
{
    long long start;
    long long finish;
    int index;
};

bool compare(job &a1, job &a2)
{
    if (a1.finish == a2.finish)
        return a1.start < a2.start;
    return a1.finish < a2.finish;
}

int main()
{
    int n;
    cin >> n;
    vector<job> activity(n);
    for (int i = 0; i < n; i++)
    {
        cin >> activity[i].start >> activity[i].finish;
        activity[i].index = i;
    }
    sort(activity.begin(), activity.end(), compare);
    vector<int> selected;
    long long last_finish = -1;
    for (auto a : activity)
    {
        if (a.start >= last_finish)
        {
            selected.push_back(a.index);
            last_finish = a.finish;
        }
    }
    cout << selected.size() << endl;
    for (auto i : selected)
        cout << i << " ";
    cout << endl;
    return 0;
}