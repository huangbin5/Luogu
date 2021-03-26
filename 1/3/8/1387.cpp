#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105;
// dp[i][j]表示以(i, j)为右下角的最大正方形边长
int n, m, a[maxn][maxn], dp[maxn][maxn] = { 0 }, ans = 0;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            if (a[i][j]) {
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                ans = max(ans, dp[i][j]);
            }
    cout << ans;
    return 0;
}