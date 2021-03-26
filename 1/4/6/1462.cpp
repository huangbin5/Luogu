#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;

struct Edge {
    int v, c;
    Edge(int _v, int _c) : v(_v), c(_c) {}
};

struct Node {
    int v, d;
    Node(int _v, int _d) : v(_v), d(_d) {}
    bool operator<(const Node& a) const { return d > a.d; }
};

const int maxn = 10005, INF = 0x7fffffff;
int n, m, blood;
int fee[maxn], min_fee = INF, max_fee = 0;
vector<Edge> G[maxn];
int dis[maxn];
bool vis[maxn] = { false };

bool dijkstra(int cur_fee) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[1] = 0;
    priority_queue<Node> pq;
    pq.push(Node(1, 0));
    while (!pq.empty()) {
        int u = pq.top().v;
        pq.pop();
        if (u == n)
            if (dis[n] < blood)
                return true;
            else
                return false;
        vis[u] = true;
        for (auto e : G[u])
            if (!vis[e.v] && dis[u] + e.c < dis[e.v] && fee[e.v] <= cur_fee) {
                dis[e.v] = dis[u] + e.c;
                pq.push(Node(e.v, dis[e.v]));
            }
    }
    return false;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m >> blood;
    for (int i = 1; i <= n; ++i) {
        cin >> fee[i];
        min_fee = min(min_fee, fee[i]);
        max_fee = max(max_fee, fee[i]);
    }
    int u, v, c;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> c;
        G[u].push_back(Edge(v, c));
        G[v].push_back(Edge(u, c));
    }
    if (!dijkstra(max_fee)) {
        cout << "AFK";
        return 0;
    }
    while (min_fee <= max_fee) {
        int mid = (min_fee + max_fee) >> 1;
        if (dijkstra(mid))
            max_fee = mid - 1;
        else
            min_fee = mid + 1;
    }
    cout << min_fee;
    return 0;
}