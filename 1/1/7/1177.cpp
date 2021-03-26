#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 100005;
int n, arr[maxn];

void getStart(int start, int end) {
    int mid = (start + end) / 2;
    if (arr[start] <= arr[mid] && arr[mid] <= arr[end])
        swap(arr[start], arr[mid]);
    else if (arr[start] <= arr[end] && arr[end] <= arr[mid])
        swap(arr[start], arr[end]);
    else if (arr[start] >= arr[mid] && arr[mid] >= arr[end])
        swap(arr[start], arr[mid]);
    else if (arr[start] >= arr[end] && arr[end] >= arr[mid])
        swap(arr[start], arr[end]);
}

int partition(int start, int end) {
    getStart(start, end);
    int left = start, right = end, tmp = arr[start];
    while (left < right) {
        while (left < right && arr[right] > tmp)
            --right;
        if (left < right)
            arr[left++] = arr[right];
        while (left < right && arr[left] < tmp)
            ++left;
        if (left < right)
            arr[right--] = arr[left];
    }
    arr[left] = tmp;
    return left;
}

void quickSort(int start, int end) {
    if (start >= end)
        return;
    int divide = partition(start, end);
    quickSort(start, divide - 1);
    quickSort(divide + 1, end);
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    quickSort(0, n - 1);
    for (int i = 0; i < n; ++i)
        if (i == n - 1)
            cout << arr[i] << endl;
        else
            cout << arr[i] << " ";
    return 0;
}