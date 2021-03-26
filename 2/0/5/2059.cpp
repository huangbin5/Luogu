#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 55;
// dp[i][j]表示i个人组成环时第j个人赢的概率
int n, m, c[maxn];
double dp[maxn][maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
        cin >> c[i];
    dp[1][1] = 100;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            for (int k = 1; k <= m; ++k)
                dp[i][j] += dp[i - 1][(j - c[k] % i + i) % i] / m;
    for (int j = 1; j < n; ++j)
        cout << fixed << setprecision(2) << dp[n][j] << "% ";
    cout << fixed << setprecision(2) << dp[n][n] << "%";
    return 0;
}