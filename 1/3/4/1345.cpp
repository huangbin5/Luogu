#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 205, maxm = 3000, INF = 0x7fffffff;
struct Edge {
    int v, flow, next;
    Edge() {}
    Edge(int _v, int _flow, int _next) : v(_v), flow(_flow), next(_next) {}
} edge[maxm];

int n, m, s, t, eNum = 1;
int head[maxn], depth[maxn];

void add_edge(int u, int v, int flow) {
    edge[++eNum] = Edge(v, flow, head[u]);
    head[u] = eNum;
    edge[++eNum] = Edge(u, 0, head[v]);
    head[v] = eNum;
}

// 分层
bool bfs() {
    memset(depth, 0, sizeof(depth));
    queue<int> q;
    q.push(s);
    depth[s] = 1;
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int i = head[u]; i; i = edge[i].next) {
            Edge e = edge[i];
            if (e.flow && !depth[e.v]) {
                q.push(e.v);
                depth[e.v] = depth[u] + 1;
                if (e.v == t)
                    return true;
            }
        }
    }
    return false;
}

// 找到增广路并更新，返回增广的流量
int dfs(int u, int in) {
    if (u == t)
        return in;
    int out = 0;
    for (int i = head[u]; i && in; i = edge[i].next) {
        Edge& e = edge[i];
        // 只往下一层走
        if (e.flow && depth[e.v] == depth[u] + 1) {
            int res = dfs(e.v, min(in, e.flow));
            // 更新
            e.flow -= res;
            edge[i ^ 1].flow += res;
            in -= res;
            out += res;
        }
    }
    // 与终点不通
    if (!out)
        depth[u] = 0;
    return out;
}

int dinic() {
    int maxFlow = 0;
    while (bfs())
        maxFlow += dfs(s + n, INF);
    return maxFlow;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m >> s >> t;
    for (int i = 1; i <= n; ++i)
        add_edge(i, i + n, 1);
    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        add_edge(u + n, v, INF);
        add_edge(v + n, u, INF);
    }
    cout << dinic();
    return 0;
}