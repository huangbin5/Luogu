#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 30000, maxm = 25;
/* dp[i][j]表示前i个物品在价格为j的情况下能达到的最大重要度
 * 若不买第i个物品，则dp[i][j] = dp[i-1][j]
 * 若买第i个物品，则dp[i][j] = dp[i-1][j-v[i]] + v[i] * w[i]
 * 综上：dp[i][j] = max{ dp[i-1][j], dp[i-1][j-v[i]] + v[i] * w[i] }
 * 使用滚动数组，则dp[j] = max{ dp[j], dp[j-v[i]] + v[i] * w[i] }
 */
int n, m, v[maxm], w[maxm], dp[maxn] = { 0 };

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
        cin >> v[i] >> w[i];
    for (int i = 1; i <= m; ++i)
        for (int j = n; j >= v[i]; --j)
            dp[j] = max(dp[j], dp[j - v[i]] + v[i] * w[i]);
    cout << dp[n];
    return 0;
}