#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 201, maxm = 7;
/**
 * a[i][j][k]表示整数i分成j份，最大(最后)的一份是k的分法
 * a[i][j][k] = sum{ a[i-k][j-1][k'], k'<=k }
 */
int n, m, a[maxn][maxm][maxn] = { 0 };

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        a[i][1][i] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            for (int k = 1; k <= i; ++k)
                for (int kk = 1; kk <= k; ++kk)
                    a[i][j][k] += a[i - k][j - 1][kk];
    int ans = 0;
    for (int k = 1; k <= n; ++k)
        ans += a[n][m][k];
    cout << ans;
    return 0;
}