#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 35;
int n, d[maxn][maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    while (cin >> n && n) {
        for (int u = 1; u <= n; ++u)
            for (int v = u + 1; v <= n; ++v) {
                cin >> d[u][v];
                d[v][u] = d[u][v];
            }
        int ans = d[1][2];
        for (int i = 3; i <= n; ++i) {
            int add = 0x3fffffff;
            for (int u = 2; u < i; ++u)
                add = min(add, (d[1][i] + d[u][i] - d[1][u]) >> 1);
            ans += add;
        }
        cout << ans << endl;
    }
    return 0;
}