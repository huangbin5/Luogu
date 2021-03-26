#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int MAXN = 1005, MAXH = 20005, MOD = 998244353;
// dp[i][j]表示以i为结尾、公差为j的方案数
int n, h[MAXN], maxh = 0, dp[MAXN][MAXH * 2] = { 0 }, ans = 0;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &h[i]);
        maxh = max(maxh, h[i]);
    }
    for (int i = 1; i <= n; ++i)
        for (int k = 1; k < i; ++k) {
            int j = h[i] - h[k] + MAXH;
            // +1是指只含i和k两个元素
            dp[i][j] = (dp[i][j] + dp[k][j] + 1) % MOD;
            // ans和dp[i][j]同步更新，相当于每个外循环累加了dp[i][]
            ans = (ans + dp[k][j] + 1) % MOD;
        }
    // 最后还要加上单个元素的情况
    printf("%d", (ans + n) % MOD);
    return 0;
}