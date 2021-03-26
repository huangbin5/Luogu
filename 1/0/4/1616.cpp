#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int v, n, c[maxn], w[maxn], dp[maxn] = { 0 };

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> v >> n;
    for (int i = 1; i <= n; ++i)
        cin >> c[i] >> w[i];
    for (int i = 1; i <= n; ++i)
        for (int j = c[i]; j <= v; ++j)
            dp[j] = max(dp[j], dp[j - c[i]] + w[i]);
    cout << dp[v];
    return 0;
}