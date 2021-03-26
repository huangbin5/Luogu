#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 15;
int n, TOP;
double x[maxn], y[maxn], dist[maxn][maxn];
// dp[i][j]表示以原点为起点i为终点，且状态为j时的总距离
// dp[i][j]=min{dp[ii][jj] + dist[ii][i]}
// jj为j中除去i的状态，ii为jj中的每一个点。对于每一对(i,j)，其jj是确定的，而ii是不确定的
double dp[maxn][1 << maxn], ans;

int main() {
#ifdef DEBUG
    freopen("d:\\data.in", "r", stdin);
    freopen("d:\\data.out", "w", stdout);
#endif
    memset(dp, 0x7f, sizeof(dp));
    cin >> n;
    TOP = (1 << n) - 1;
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
        for (int j = 0; j < i; ++j)
            dist[i][j] = dist[j][i] = hypot(x[i] - x[j], y[i] - y[j]);
    }
    // 状态从小到大遍历
    for (int j = 1; j <= (TOP); ++j) {
        for (int i = 0; i < n; ++i) {
            // j中不包含i，非法
            if ((j & (1 << i)) == 0)
                continue;
            // jj为j中除i的状态
            int jj = (j ^ (1 << i));
            // j中只包含i，dp[i][j]就等于从原点到i的距离
            if (jj == 0) {
                dp[i][j] = hypot(x[i], y[i]);
                continue;
            }
            // ii为jj中的每一个点
            for (int ii = 0; ii < n; ++ii) {
                if ((jj & (1 << ii)) != 0)
                    dp[i][j] = min(dp[i][j], dp[ii][jj] + dist[ii][i]);
            }
        }
    }
    ans = dp[0][TOP];
    for (int i = 1; i < n; ++i)
        ans = min(ans, dp[i][TOP]);
    cout << fixed << setprecision(2) << ans;
    return 0;
}