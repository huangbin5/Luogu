#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105, maxm = 205;
// dp[i][j][k]表示前i个愿望在钱为j和时间为k时能得到满足的个数
int n, m, t, mon[maxn], tim[maxn], dp[maxm][maxm] = { 0 };

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m >> t;
    for (int i = 1; i <= n; ++i)
        cin >> mon[i] >> tim[i];
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= mon[i]; --j)
            for (int k = t; k >= tim[i]; --k)
                dp[j][k] = max(dp[j][k], dp[j - mon[i]][k - tim[i]] + 1);
    cout << dp[m][t];
    return 0;
}