#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 20005, maxm = 100005, INF = 0x3fffffff;
struct Edge {
    int u, v, d;
    Edge() {}
    Edge(int _u, int _v, int _d) : u(_u), v(_v), d(_d) {}
    bool operator<(const Edge& tmp) const { return d > tmp.d; }
} edge[maxm];

int n, m, up[maxn], enemy[maxn] = { 0 };

inline int read() {
    int x = 0, sign = 1;
    char c = getchar();
    // 符号
    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            sign = -1;
    // 多位数字
    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    return x * sign;
}

void init() {
    for (int i = 1; i <= n; ++i)
        up[i] = i;
}

int find(int x) {
    if (x == up[x])
        return x;
    return up[x] = find(up[x]);
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    init();
    int u, v, d;
    for (int i = 0; i < m; ++i) {
        u = read(), v = read(), d = read();
        edge[i] = Edge(u, v, d);
    }
    sort(edge, edge + m);
    for (int i = 0; i < m; ++i) {
        int u = edge[i].u, v = edge[i].v;
        int uu = find(u), vv = find(v);
        if (uu == vv) {
            cout << edge[i].d;
            return 0;
        }
        enemy[u] ? up[vv] = find(enemy[u]) : enemy[u] = v;
        enemy[v] ? up[uu] = find(enemy[v]) : enemy[v] = u;
    }
    cout << 0;
    return 0;
}