#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 250;
// dp[i][j]表示i~j完全合并得到的最大值
int n, a[maxn], dp[maxn][maxn] = { 0 }, ans = 0;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        dp[i][i] = a[i];
        ans = max(ans, dp[i][i]);
    }
    for (int len = 2; len <= n; ++len)
        for (int i = 1, j = i + len - 1; j <= n; ++i, ++j)
            for (int k = i; k < j; ++k)
                if (dp[i][k] != 0 && dp[i][k] == dp[k + 1][j]) {
                    dp[i][j] = dp[i][k] + 1;
                    ans = max(ans, dp[i][j]);
                }
    cout << ans;
    return 0;
}