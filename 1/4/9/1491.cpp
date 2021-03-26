#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;

struct Edge {
    int v;
    double d;
    Edge(){};
    Edge(int _v, double _d) : v(_v), d(_d){};
    // 优先级队列中维护的节点距离信息。自定义优先级，函数必须为const
    bool operator<(const Edge& tmp) const { return d > tmp.d; }
};

struct Node {
    double x, y;
    Node() {}
    Node(double _x, double _y) : x(_x), y(_y) {}
};

const int maxn = 205;
const double INF = numeric_limits<double>::max();
int n, m;
Node node[maxn];
vector<Edge> G[maxn];
double dis[maxn];
int pre[maxn];
bool vis[maxn];
int ex_u = 0, ex_v = 0;
double shortest2 = INF;

void dijkstra_heap(int s, bool first) {
    for (int i = 0; i <= n; ++i)
        dis[i] = INF;
    memset(vis, false, sizeof(vis));
    if (first)
        // 初始化前驱
        for (int u = 1; u <= n; ++u)
            pre[u] = u;
    dis[s] = 0;
    priority_queue<Edge> pq;
    pq.push(Edge(s, 0));
    while (!pq.empty()) {
        // 找到剩余节点中距离最近者u
        int u = pq.top().v;
        pq.pop();
        // 因为某个节点可能被之前的多个节点更新距离而入队，因此队列中可能会有相同的节点
        if (vis[u])
            continue;
        vis[u] = true;
        // 更新与u相邻顶点的距离指标
        for (auto e : G[u])
            if (u + e.v != ex_u + ex_v || u - e.v != ex_u - ex_v)
                if (!vis[e.v] && dis[u] + e.d < dis[e.v]) {
                    dis[e.v] = dis[u] + e.d;
                    pq.push(Edge(e.v, dis[e.v]));
                    if (first)
                        pre[e.v] = u;
                }
    }
    // 更新第二段路径
    if (vis[n] && !first)
        shortest2 = min(shortest2, dis[n]);
}

void ex_dijkstra(int v) {
    if (pre[v] == v)
        return;
    ex_u = pre[v];
    ex_v = v;
    dijkstra_heap(1, false);
    ex_dijkstra(pre[v]);
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int u = 1; u <= n; ++u)
        cin >> node[u].x >> node[u].y;
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        double d = hypot(node[u].x - node[v].x, node[u].y - node[v].y);
        G[u].push_back(Edge(v, d));
        G[v].push_back(Edge(u, d));
    }
    dijkstra_heap(1, true);
    if (!vis[n]) {
        cout << -1;
        return 0;
    }
    ex_dijkstra(n);
    if (shortest2 == INF)
        cout << -1;
    else
        cout << fixed << setprecision(2) << shortest2;
    return 0;
}