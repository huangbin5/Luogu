#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 105, maxm = 5005;
struct Edge {
    int v, d, next;
    Edge() {}
    Edge(int _v, int _d, int _next = 0) : v(_v), d(_d), next(_next) {}
    bool operator<(const Edge& tmp) const { return d > tmp.d; }
} edge[maxm * 2];
int head[maxn] = { 0 };

int n, m, cnt = 0;
int dis[maxn];
bool vis[maxn];
int min1, min2 = 0;

void add_edge(int u, int d, int v) {
    edge[++cnt] = Edge(v, d, head[u]);
    head[u] = cnt;
}

bool dijkstra(int s) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    for (int i = 1; i <= n; ++i) {
        // 找到剩余节点中距离最近者u
        int u = 0;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && dis[j] < dis[u])
                u = j;
        // 找不到说明还有节点无法到达
        if (!u)
            return false;
        vis[u] = true;
        // 更新与u相邻顶点的距离指标
        for (int i = head[u]; i; i = edge[i].next) {
            Edge e = edge[i];
            if (dis[u] + e.d < dis[e.v])
                dis[e.v] = dis[u] + e.d;
        }
    }
    return true;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    int u, v, d;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> d;
        add_edge(u, d, v);
        add_edge(v, d, u);
    }
    dijkstra(1);
    min1 = dis[n];
    for (int i = 1; i <= cnt; i += 2) {
        edge[i].d <<= 1;
        edge[i + 1].d <<= 1;
        dijkstra(1);
        min2 = max(min2, dis[n]);
        edge[i].d >>= 1;
        edge[i + 1].d >>= 1;
    }
    cout << min2 - min1;
    return 0;
}