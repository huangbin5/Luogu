#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

const int INF = 0x7fffffff, maxn = 1e4 + 5, maxm = 1e5 + 5;
int head[maxn], depth[maxn];
int n, m, s, t, eNum = 1;

struct Edge {
    int v, flow, next;
    Edge() {}
    Edge(int _v, int _flow, int _next) : v(_v), flow(_flow), next(_next) {}
} edge[maxm * 2];

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
        maxFlow += dfs(s, INF);
    return maxFlow;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    memset(head, 0, sizeof(head));
    scanf("%d %d", &n, &m);
    scanf("%d %d", &s, &t);
    int u, v, flow;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &flow);
        add_edge(u, v, flow);
    }
    printf("%d\n", dinic());
    return 0;
}