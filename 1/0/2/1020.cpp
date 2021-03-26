#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 100005;
// a和b分别为“最长不上升子序列”和“最长上升子序列”
int n = 0, height[maxn], a[maxn] = { 0 }, b[maxn] = { 0 }, len1 = 0, len2 = 0;

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    while (cin >> height[n + 1])
        ++n;
    for (int i = 1; i <= n; ++i) {
        if (len1 == 0 || height[i] <= a[len1 - 1])
            a[len1++] = height[i];
        else
            *upper_bound(a, a + len1, height[i], greater<int>()) = height[i];
        if (len2 == 0 || height[i] > b[len2 - 1])
            b[len2++] = height[i];
        else
            *lower_bound(b, b + len2, height[i]) = height[i];
    }
    cout << len1 << endl << len2;
    return 0;
}