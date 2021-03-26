#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 20005;
int v, n, c[maxn], dp[maxn] = { 0 };

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> v >> n;
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    for (int i = 1; i <= n; ++i)
        for (int j = v; j >= c[i]; --j)
            dp[j] = max(dp[j], dp[j - c[i]] + c[i]);
    cout << v - dp[v];
    return 0;
}