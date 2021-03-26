#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5;
int n, m, a[maxn];

bool check(int mid) {
    int cnt = 1, left = 0;
    for (int right = 1; right < n; ++right) {
        if (a[right] - a[left] >= mid) {
            left = right;
            ++cnt;
            if (cnt >= m)
                return true;
        }
    }
    return false;
}

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    sort(a, a + n);
    int left = 1e9, right = a[n - 1] - a[0];
    for (int i = 1; i < n; ++i)
        left = min(left, a[i] - a[i - 1]);
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (check(mid))
            left = mid + 1;
        else
            right = mid - 1;
    }
    cout << right;
    return 0;
}