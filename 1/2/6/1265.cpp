#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 5005;
int n;
double x[maxn], y[maxn];
double dis[maxn];
bool vis[maxn];

double cacul(int u, int v) { return hypot(x[u] - x[v], y[u] - y[v]); }

double prim() {
    memset(dis, 0x7f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[1] = 0;
    double ans = 0;
    for (int i = 1; i <= n; ++i) {
        int u = 0;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && dis[j] < dis[u])
                u = j;
        if (!u)
            return -1;
        vis[u] = true;
        ans += dis[u];
        for (int v = 1; v <= n; ++v)
            if (cacul(u, v) < dis[v])
                dis[v] = cacul(u, v);
    }
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int u = 1; u <= n; ++u)
        cin >> x[u] >> y[u];
    cout << fixed << setprecision(2) << prim();
    return 0;
}