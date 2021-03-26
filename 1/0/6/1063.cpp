#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105;
// 第i个点左边的标记下标为i，右边的标记下标为i+1
int n, energy[maxn], dp[2 * maxn][2 * maxn] = { 0 }, ans = 0;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> energy[i];
    for (int len = 2; len <= n; ++len)
        for (int i = 0, j = i + len - 1; j < 2 * n; ++i, ++j)
            for (int k = i; k < j; ++k)
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + energy[i % n] * energy[(k + 1) % n] * energy[(j + 1) % n]);
    for (int i = 0; i < n; ++i)
        ans = max(ans, dp[i][i + n - 1]);
    cout << ans;
    return 0;
}