#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1005;
// 分组背包：dp[i][j]表示前i个骨牌上面的数字之和为j所需要最少的翻转次数
int n, up[maxn], down[maxn], sum = 0, dp[maxn][6 * maxn] = { 0 };

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    fill(dp[0], dp[0] + maxn * maxn, maxn);
    dp[0][0] = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> up[i] >> down[i];
        sum += up[i] + down[i];
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= sum; ++j) {
            int tmp = maxn;
            if (j - up[i] >= 0)
                tmp = min(tmp, dp[i - 1][j - up[i]]);
            if (j - down[i] >= 0)
                tmp = min(tmp, dp[i - 1][j - down[i]] + 1);
            dp[i][j] = tmp;
        }
    // for (int i = 0; i <= n; ++i) {
    //     if (i)
    //         cout << setw(3) << right << i;
    //     else
    //         cout << setw(3) << right << ' ';
    //     for (int j = 1; j <= sum; ++j) {
    //         if (i)
    //             cout << setw(6) << right << dp[i][j];
    //         else
    //             cout << setw(6) << right << j;
    //     }
    //     cout << endl;
    // }
    for (int i = sum >> 1; i > 0; --i) {
        int tmp = min(dp[n][i], dp[n][sum - i]);
        if (tmp < maxn) {
            cout << tmp;
            break;
        }
    }
    return 0;
}