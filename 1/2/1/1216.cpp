#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1005;
// dp[i][j] = max(dp[i-1][j-1], dp[i-1][j]) + num[i][j]
int n, num[maxn], dp[maxn];

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j)
            cin >> num[j];
        for (int j = i; j >= 1; --j)
            dp[j] = max(dp[j - 1], dp[j]) + num[j];
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = max(ans, dp[i]);
    cout << ans;
    return 0;
}