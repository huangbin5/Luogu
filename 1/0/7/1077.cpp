#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105, MOD = 1000007;
int m, n, a[maxn], dp[maxn][maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int k = max(0, j - a[i]); k <= j; ++k)
                dp[i][j] = (dp[i][j] + dp[i - 1][k]) % MOD;
    cout << dp[n][m];
    return 0;
}