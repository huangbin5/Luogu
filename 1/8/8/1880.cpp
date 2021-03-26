#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

// dp[i][j]表示合并i~j所需要的花费，dp[i][j] = max/min(dp[i][k] + dp[k][j]) + sum[i,j]
const int maxn = 205, INF = 0x7fffffff;
int n, a[maxn], sum[maxn], dp1[maxn][maxn] = { 0 }, dp2[maxn][maxn];

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum[i] = i ? sum[i - 1] + a[i] : a[i];
    }
    for (int i = n; i < 2 * n; ++i) {
        a[i] = a[i - n];
        sum[i] = sum[i - 1] + a[i];
    }
    fill(dp2[0], dp2[0] + maxn * maxn, INF);
    for (int i = 0; i < 2 * n; ++i)
        dp1[i][i] = dp2[i][i] = 0;
    for (int len = 1; len < n; ++len)
        for (int i = 0, j = len; j < 2 * n; ++i, ++j)
            for (int k = i; k < j; ++k) {
                dp1[i][j] = max(dp1[i][j], dp1[i][k] + dp1[k + 1][j] + sum[j] - sum[i] + a[i]);
                dp2[i][j] = min(dp2[i][j], dp2[i][k] + dp2[k + 1][j] + sum[j] - sum[i] + a[i]);
            }
    int ans1 = 0, ans2 = INF;
    for (int i = 0, j = n - 1; j < 2 * n; ++i, ++j) {
        ans1 = max(ans1, dp1[i][j]);
        ans2 = min(ans2, dp2[i][j]);
    }
    cout << ans2 << endl << ans1;
    return 0;
}