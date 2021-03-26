#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 1505;
int n, m, x1, y1, x2, y2, G[maxn][maxn];
int dis1[maxn], dis2[maxn], dp[maxn], ans = 0;
bool inq[maxn];
bool flag[maxn][maxn], flag1[maxn][maxn], flag2[maxn][maxn];

void spfa(int s, int dis[]) {
    memset(dis, 0x3f, sizeof(int) * maxn);
    memset(inq, false, sizeof(inq));
    dis[s] = 0;
    queue<int> q;
    q.push(s);
    inq[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v = 1; v <= n; ++v)
            if (G[u][v] && dis[u] + G[u][v] < dis[v]) {
                dis[v] = dis[u] + G[u][v];
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
    }
}

int dfs(int v, bool fg[][maxn]) {
    if (!dp[v])
        for (int u = 1; u <= n; ++u)
            if (flag[u][v] && fg[u][v])
                dp[v] = max(dp[v], dfs(u, fg) + G[u][v]);
    ans = max(ans, dp[v]);
    return dp[v];
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m >> x1 >> y1 >> x2 >> y2;
    int u, v, d;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> d;
        G[u][v] = G[v][u] = d;
    }
    spfa(x1, dis1);
    spfa(y1, dis2);
    memset(flag, false, sizeof(flag));
    for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v)
            if (G[u][v] && dis1[u] + G[u][v] + dis2[v] == dis1[y1])
                flag[u][v] = true;

    spfa(x2, dis1);
    spfa(y2, dis2);
    memset(flag1, false, sizeof(flag1));
    memset(flag2, false, sizeof(flag2));
    for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v) {
            if (G[u][v] && dis1[u] + G[u][v] + dis2[v] == dis1[y2])
                flag1[u][v] = true;
            if (G[u][v] && dis2[u] + G[u][v] + dis1[v] == dis2[x2])
                flag2[u][v] = true;
        }
    memset(dp, 0, sizeof(dp));
    for (int u = 1; u <= n; ++u)
        dfs(u, flag1);
    memset(dp, 0, sizeof(dp));
    for (int u = 1; u <= n; ++u)
        dfs(u, flag2);
    cout << ans;
    return 0;
}