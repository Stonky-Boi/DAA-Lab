// Sort using bubble, merge, quick
// Print execution time in milliseconds

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

void bubble_sort(vector<int> &v)
{
    int n = v.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (v[j] > v[j + 1])
                swap(v[j], v[j + 1]);
}

void merge(vector<int> &v, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<int> left(n1), right(n2);
    for (int i = 0; i < n1; i++)
        left[i] = v[l + i];
    for (int i = 0; i < n2; i++)
        right[i] = v[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        if (left[i] <= right[j])
            v[k++] = left[i++];
        else
            v[k++] = right[j++];
    while (i < n1)
        v[k++] = left[i++];
    while (j < n2)
        v[k++] = right[j++];
}

void merge_sort(vector<int> &v, int l, int r)
{
    if (l >= r)
        return;
    int m = l + (r - l) / 2;
    merge_sort(v, l, m);
    merge_sort(v, m + 1, r);
    merge(v, l, m, r);
}

int partition(vector<int> &v, int l, int r)
{
    int pivot = v[r];
    int i = l - 1;
    for (int j = l; j < r; j++)
        if (v[j] <= pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    swap(v[i + 1], v[r]);
    return i + 1;
}

void quick_sort(vector<int> &v, int l, int r)
{
    if (l < r)
    {
        int p = partition(v, l, r);
        quick_sort(v, l, p - 1);
        quick_sort(v, p + 1, r);
    }
}

int main()
{
    int n;
    cin >> n;
    vector<int> num(n);
    for (auto &i : num)
        cin >> i;
    vector<int> bubble_array = num;
    vector<int> merge_array = num;
    vector<int> quick_array = num;
    auto bubble_start = chrono::high_resolution_clock::now();
    bubble_sort(bubble_array);
    auto bubble_end = chrono::high_resolution_clock::now();
    auto merge_start = chrono::high_resolution_clock::now();
    merge_sort(merge_array, 0, n - 1);
    auto merge_end = chrono::high_resolution_clock::now();
    auto quick_start = chrono::high_resolution_clock::now();
    quick_sort(quick_array, 0, n - 1);
    auto quick_end = chrono::high_resolution_clock::now();
    bool unchanged = true;
    for (int i = 0; i < n; i++)
        if (num[i] != merge_array[i])
        {
            unchanged = false;
            break;
        }
    if (unchanged)
        cout << "Sorted output remains unchanged" << endl;
    else
    {
        for (int x : merge_array)
            cout << x << " ";
        cout << endl;
    }
    cout << "BubbleSort: " << chrono::duration_cast<chrono::milliseconds>(bubble_end - bubble_start).count() << " ms" << endl;
    cout << "MergeSort: " << chrono::duration_cast<chrono::milliseconds>(merge_end - merge_start).count() << " ms" << endl;
    cout << "QuickSort: " << chrono::duration_cast<chrono::milliseconds>(quick_end - quick_start).count() << " ms" << endl;
    return 0;
}