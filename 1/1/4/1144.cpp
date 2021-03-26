#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

struct Edge {
    int v, d;
    Edge() {}
    Edge(int _v, int _d) : v(_v), d(_d) {}
    // 优先级队列中维护的节点距离信息。自定义优先级，函数必须为const
    bool operator<(const Edge& tmp) const { return d > tmp.d; }
};

const int maxn = 1e6 + 5, MOD = 100003;
int n, m;
vector<int> G[maxn];
int dis[maxn], num[maxn];
bool vis[maxn];

void dijkstra_heap(int s) {
    memset(dis, 0x3f, sizeof(dis));
    memset(num, 0, sizeof(num));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    num[s] = 1;
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
        for (auto v : G[u])
            if (dis[u] + 1 < dis[v]) {
                dis[v] = dis[u] + 1;
                num[v] = num[u];
                pq.push(Edge(v, dis[v]));
            } else if (dis[u] + 1 == dis[v])
                num[v] = (num[v] + num[u]) % MOD;
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dijkstra_heap(1);
    for (u = 1; u <= n; ++u)
        cout << num[u] << endl;
    return 0;
}