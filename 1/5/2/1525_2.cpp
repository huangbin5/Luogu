#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 20005, maxm = 100005, INF = 0x3fffffff;
struct Edge {
    int v, d;
    Edge() {}
    Edge(int _v, int _d) : v(_v), d(_d) {}
} edge[maxm];

int n, m;
vector<Edge> G[maxn];
int color[maxn], maxD;

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

bool dfs(int u, int c = 1) {
    color[u] = c;
    for (auto e : G[u])
        if (e.d > maxD) {
            if (color[e.v] == color[u])
                return false;
            if (!color[e.v] && !dfs(e.v, -c))
                return false;
        }
    return true;
}

bool is_bigraph() {
    for (int u = 1; u <= n; ++u)
        if (!color[u] && !dfs(u))
            return false;
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
    int left = 0, right = 0;
    for (int i = 0; i < m; ++i) {
        u = read(), v = read(), d = read();
        right = max(right, d);
        G[u].push_back(Edge(v, d));
        G[v].push_back(Edge(u, d));
    }
    while (left <= right) {
        maxD = (left + right) >> 1;
        memset(color, 0, sizeof(color));
        if (is_bigraph())
            right = maxD - 1;
        else
            left = maxD + 1;
    }
    cout << left;
    return 0;
}