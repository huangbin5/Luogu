#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 10005;
int n, tim[maxn], dp[maxn] = { 0 };

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    int u, ans = 0;
    for (int v = 1; v <= n; ++v) {
        cin >> tim[v] >> tim[v];
        while (cin >> u && u)
            dp[v] = max(dp[v], dp[u]);
        dp[v] += tim[v];
        ans = max(ans, dp[v]);
    }
    cout << ans;
    return 0;
}