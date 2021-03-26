#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;
// dp[i]表示长度为i的LIS末尾的最小值
int n, a[maxn], idx[maxn], dp[maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d", &n);
    // 记录数字在a中出现的下标
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
        idx[a[i]] = i;
    }
    int tmp;
    // 将b中的数字转化为该数字在a中的下标
    // 求最长上升子序列LIS
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &tmp);
        *lower_bound(dp + 1, dp + n + 1, idx[tmp]) = idx[tmp];
    }
    printf("%d", lower_bound(dp + 1, dp + n + 1, dp[0]) - dp - 1);
    return 0;
}