#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 355, maxm = 41;
int n, m, score[maxn], num[5] = { 0 };
int dp[maxm][maxm][maxm][maxm] = { 0 };

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> score[i];
    int step;
    for (int i = 0; i < m; ++i) {
        cin >> step;
        ++num[step];
    }
    for (int i = 0; i <= num[1]; ++i)
        for (int j = 0; j <= num[2]; ++j)
            for (int k = 0; k <= num[3]; ++k)
                for (int l = 0; l <= num[4]; ++l) {
                    if (i)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i - 1][j][k][l]);
                    if (j)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j - 1][k][l]);
                    if (k)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k - 1][l]);
                    if (l)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k][l - 1]);
                    dp[i][j][k][l] += score[i + 2 * j + 3 * k + 4 * l];
                }
    cout << dp[num[1]][num[2]][num[3]][num[4]];
    return 0;
}