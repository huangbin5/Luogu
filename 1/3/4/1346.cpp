#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

struct Edge {
    int v, d;
    Edge(int _v, int _d) : v(_v), d(_d) {}
};
const int maxn = 105;
int n, A, B;
vector<Edge> G[maxn];
int dis[maxn];
bool vis[maxn];

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
        if (u == B)
            return true;
        // 找不到说明还有节点无法到达
        if (!u)
            return false;
        vis[u] = true;
        // 更新与u相邻顶点的距离指标
        for (auto e : G[u])
            if (!vis[e.v] && dis[u] + e.d < dis[e.v])
                dis[e.v] = dis[u] + e.d;
    }
    return true;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> A >> B;
    int k, v;
    for (int u = 1; u <= n; ++u) {
        cin >> k;
        for (int i = 0; i < k; ++i) {
            cin >> v;
            G[u].push_back(Edge(v, i != 0));
        }
    }
    if (dijkstra(A))
        cout << dis[B];
    else
        cout << -1;
    return 0;
}