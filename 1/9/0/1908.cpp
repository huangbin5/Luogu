#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 5 * 1e5 + 5;
int n, arr[maxn], tmp[maxn];

ll mergeSort(int left, int right) {
    if (left >= right)
        return 0;
    int mid = (left + right) >> 1;
    ll res = mergeSort(left, mid) + mergeSort(mid + 1, right);
    for (int i = left; i <= mid; ++i)
        tmp[i] = arr[i];
    int p1 = left, p2 = mid + 1, p3 = left;
    while (p1 <= mid && p2 <= right) {
        if (tmp[p1] <= arr[p2])
            arr[p3++] = tmp[p1++];
        else {
            arr[p3++] = arr[p2++];
            res += mid - p1 + 1;
        }
    }
    while (p1 <= mid)
        arr[p3++] = tmp[p1++];
    return res;
}

int main() {
#ifdef DEBUG
    freopen("d:\\data.in", "r", stdin);
    freopen("d:\\data.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    cout << mergeSort(0, n - 1);
    return 0;
}