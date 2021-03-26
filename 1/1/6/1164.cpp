#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105, maxm = 10005;
/**
 * dp[i][j]表示前i种菜刚好花完j元的方案数
 * 若没点第i种菜，则dp[i][j] = dp[i-1][j]
 * 若点了第i种菜，则dp[i][j] = dp[i-1][j-v[i]] + 1
 * 综上：dp[i][j] = dp[i-1][j] + dp[i-1][j-v[i]]
 * 使用滚动数组：dp[j] = dp[j] + dp[j-v[i]]
 */
int n, m, v[maxn], dp[maxm] = { 0 };

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        cin >> v[i];
    dp[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = m; j >= v[i]; --j)
            dp[j] = dp[j] + dp[j - v[i]];
    cout << dp[m];
    return 0;
}