#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int n, m, num[maxn];

bool check(int mid) {
    int cnt = 1, sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += num[i];
        if (sum > mid) {
            sum = num[i];
            ++cnt;
            if (cnt > m)
                return false;
        }
    }
    return true;
}

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    int left = 0, right = 0;
    for (int i = 0; i < n; ++i) {
        cin >> num[i];
        left = max(left, num[i]);
        right += num[i];
    }
    while (left <= right) {
        int mid = (left + right) >> 1;
        if (check(mid))
            right = mid - 1;
        else
            left = mid + 1;
    }
    cout << left;
    return 0;
}