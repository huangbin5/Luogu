#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 205;
int m, n, a[maxn][maxn], dp[maxn][maxn] = { 0 };

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> m >> n;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            cin >> a[i][j];
    for (int j = 0; j < n; ++j)
        dp[0][j] = a[0][j];
    for (int i = 1; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j - 1 >= 0)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1]);
            if (j + 1 < n)
                dp[i][j] = max(dp[i][j], dp[i - 1][j + 1]);
            dp[i][j] += a[i][j];
        }
    cout << max(max(dp[m - 1][(n >> 1) - 1], dp[m - 1][n >> 1]), dp[m - 1][(n >> 1) + 1]);
    return 0;
}