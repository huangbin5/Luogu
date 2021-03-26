#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 205, INF = 0x3f3f3f3f;
int n, m, q, dis[maxn][maxn];
int tim[maxn];

void floyd() {
    memset(dis, 0x3f, sizeof(dis));
    // 依次加入中介点
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dis[i][k] + dis[k][j] < dis[i][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int u, v, d;
    cin >> n >> m;
    for (int u = 0; u < n; ++u)
        cin >> tim[u];
    memset(dis, 0x3f, sizeof(dis));
    for (u = 0; u < n; ++u)
        dis[u][u] = 0;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> d;
        dis[u][v] = d;
        dis[v][u] = d;
    }
    cin >> q;
    int x, y, t, k = 0;
    for (int i = 0; i < q; ++i) {
        cin >> x >> y >> t;
        for (; k < n && tim[k] <= t; ++k)
            for (u = 0; u < n; ++u)
                for (v = 0; v < n; ++v)
                    if (dis[u][k] + dis[k][v] < dis[u][v])
                        dis[u][v] = dis[u][k] + dis[k][v];
        if (t < tim[x] || t < tim[y] || dis[x][y] == INF)
            cout << -1 << endl;
        else
            cout << dis[x][y] << endl;
    }
    return 0;
}