#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Rubbish {
    int t, h, e;
    Rubbish() {}
    bool operator<(Rubbish& a) { return t < a.t; }
};

const int maxn = 105, maxh = 1005;
int h, n;
Rubbish rub[maxn];
// dp[i][j]表示前i个垃圾到达高度j时能维持的最大生命时间
int dp[maxn][maxh + 25] = { 0 };

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> h >> n;
    for (int i = 1; i <= n; ++i)
        cin >> rub[i].t >> rub[i].e >> rub[i].h;
    sort(rub + 1, rub + n + 1);
    dp[0][0] = 10;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= h + 25; ++j) {
            // 要活着
            if (dp[i - 1][j] >= rub[i].t)
                // 用来吃
                dp[i][j] = dp[i - 1][j] + rub[i].e;
            // 要活着
            if (j >= rub[i].h && dp[i - 1][j - rub[i].h] >= rub[i].t) {
                if (j >= h) {
                    cout << rub[i].t;
                    return 0;
                }
                // 用来填高度
                dp[i][j] = max(dp[i][j], dp[i - 1][j - rub[i].h]);
            }
        }
    // 如若无法出去，最大存活时间就是依次吃掉每个垃圾所能坚持的时间
    int idx;
    for (idx = 0; idx < n; ++idx)
        if (dp[idx + 1][0] == 0)
            break;
    cout << dp[idx][0];
    return 0;
}