#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 10005, maxm = 30005;
int n, m, eNum;
int dis[maxn];
bool vis[maxn];

// 边结构，存储终点和下一条同起点边的下标
struct Edge {
    int v, d, next;
    Edge() {}
    Edge(int _v, int _d, int _next) : v(_v), d(_d), next(_next) {}
} edge[maxm];
int head[maxn];

void add_edge(int u, int v, int d) {
    edge[++eNum] = Edge(v, d, head[u]);
    head[u] = eNum;
}

bool spfa(int u) {
    vis[u] = true;
    for (int i = head[u]; i; i = edge[i].next) {
        Edge e = edge[i];
        if (dis[u] + e.d > dis[e.v]) {
            dis[e.v] = dis[u] + e.d;
            if (vis[e.v])
                return false;
            if (!spfa(e.v))
                return false;
        }
    }
    vis[u] = false;
    return true;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int u = 1; u <= n; ++u)
        add_edge(0, u, 0);
    int t, u, v, d;
    for (int i = 0; i < m; ++i) {
        cin >> t >> u >> v;
        if (t == 3) {
            add_edge(u, v, 0);
            add_edge(v, u, 0);
        } else {
            cin >> d;
            if (t == 1)
                add_edge(v, u, d);
            else
                add_edge(u, v, -d);
        }
    }
    memset(dis, 0xf1, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[0] = 0;
    if (spfa(0))
        cout << "Yes";
    else
        cout << "No";
    return 0;
}