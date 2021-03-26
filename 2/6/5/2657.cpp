#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 2000000005;
ll L, R, dp[15][10] = { 0 };

ll cacul(int n) {
    ll a[15] = { 0 }, t = 0, ans = 0;
    while (n > 0)
        a[t++] = n % 10, n /= 10;
    // 位数小于n的位数都满足
    for (int i = 1; i < t; ++i)
        // 注意最高位不能为0
        for (int j = 1; j <= 9; ++j)
            ans += dp[i][j];
    // 位数等于n的位数，但最高位小于n的最高位
    for (int i = 1; i < a[t - 1]; ++i)
        ans += dp[t][i];
    // 最高的几位都相等，第i位小于n的第i位
    for (int i = t - 1; i >= 1; --i) {
        for (int j = 0; j < a[i - 1]; ++j)
            if (abs(j - a[i]) > 1)
                ans += dp[i][j];
        if (abs(a[i - 1] - a[i]) < 2)
            break;
    }
    return ans;
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> L >> R;
    for (int i = 0; i <= 9; ++i)
        dp[1][i] = 1;
    for (int i = 2; i <= 10; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = 0; k <= 9; ++k)
                if (abs(j - k) > 1)
                    dp[i][j] += dp[i - 1][k];
    cout << cacul(R + 1) - cacul(L);
    return 0;
}