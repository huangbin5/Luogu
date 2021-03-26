#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, G[maxn][maxn];
int dis[maxn];
bool vis[maxn];

int prim(int s) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    int ans = 0;
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
            if (G[u][v] < dis[v])
                dis[v] = G[u][v];
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
    int d;
    for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v)
            cin >> G[u][v];
    cout << prim(1);
    return 0;
}