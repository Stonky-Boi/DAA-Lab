// Sort by frequency
// Preserve relative order if equal

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

map<int, int> freq;
map<int, int> first_index;

bool compare(int a, int b)
{
    if (freq[a] != freq[b])
        return freq[a] > freq[b];
    return first_index[a] < first_index[b];
}

int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    vector<int> unique;
    for (int i = 0; i < n; i++)
    {
        cin >> num[i];
        if (freq[num[i]] == 0)
            unique.push_back(num[i]);
        freq[num[i]]++;
        if (first_index.find(num[i]) == first_index.end())
            first_index[num[i]] = i;
    }
    sort(unique.begin(), unique.end(), compare);
    cout << "[ ";
    for (int i : unique)
        for (int i = 0; i < freq[i]; i++)
            cout << i << " ";
    cout << "]" << endl;
    return 0;
}