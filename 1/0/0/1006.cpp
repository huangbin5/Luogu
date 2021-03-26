#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 55;
int m, n, a[maxn][maxn];
// int dp[2 * maxn][maxn][maxn] = { 0 };
int dp[maxn][maxn] = { 0 };

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> m >> n;
    for (int i = 1; i <= m; ++i)
        for (int j = 1; j <= n; ++j)
            cin >> a[i][j];
    // for (int ij = 2; ij < m + n; ++ij)
    //     for (int i = 1; i < ij && i <= n; ++i)
    //         for (int j = i + 1; j < ij && j <= n; ++j)
    //             dp[ij][i][j]
    //                 = max(max(dp[ij - 1][i][j], dp[ij - 1][i - 1][j]), max(dp[ij - 1][i][j - 1], dp[ij - 1][i - 1][j - 1]))
    //                 + a[ij - i][i] + a[ij - j][j];
    // cout << dp[m + n - 1][n - 1][n];
    for (int ij = 2; ij < m + n; ++ij)
        for (int i = min(ij - 1, n); i >= 1; --i)
            for (int j = min(ij - 1, n); j > i; --j)
                dp[i][j] = max(max(dp[i][j], dp[i - 1][j]), max(dp[i][j - 1], dp[i - 1][j - 1])) + a[ij - i][i] + a[ij - j][j];
    cout << dp[n - 1][n];
    return 0;
}