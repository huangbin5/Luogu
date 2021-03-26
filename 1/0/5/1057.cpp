#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 31;
/**
 * dp[i][j]表示经过i次传球，传到j手上的可能情况数
 * dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1]
 */
int n, m, dp[maxn][maxn] = { 0 };

int main() {
#define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    dp[0][0] = 1;
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j < n; ++j)
            dp[i][j] = dp[i - 1][(j + n - 1) % n] + dp[i - 1][(j + 1) % n];
    cout << dp[m][0];
    return 0;
}