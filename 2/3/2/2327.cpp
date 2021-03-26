#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 10005;
int n, a[maxn] = { 0 }, dp[maxn][10] = { 0 };

int one(int i, int j) {
    if (i == 0)
        return 0;
    if (i == 1 && (j & 4))
        return 10;
    if (i == n && (j & 1))
        return 10;
    if (j == 0)
        return 0;
    if (j == 7)
        return 3;
    if (j == 1 || j == 2 || j == 4)
        return 1;
    return 2;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    dp[0][0] = dp[0][1] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 8; ++j)
            if (one(i, j) == a[i]) {
                if (one(i - 1, j >> 1) == a[i - 1])
                    dp[i][j] += dp[i - 1][j >> 1];
                if (one(i - 1, (j >> 1) + 4) == a[i - 1])
                    dp[i][j] += dp[i - 1][(j >> 1) + 4];
            }
    int ans = 0;
    for (int j = 0; j < 8; ++j)
        ans += dp[n][j];
    cout << ans;
    return 0;
}