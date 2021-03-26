#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 500005;
struct Edge {
    int v, next;
    Edge() {}
    Edge(int _v, int _next) : v(_v), next(_next) {}
} G[maxn * 2];
int head[maxn];
int n, m, s, eNum = 0;
int depth[maxn];
int dp[maxn][21];

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

void add_edge(int u, int v) {
    G[++eNum] = Edge(v, head[u]);
    head[u] = eNum;
}

void dfs(int u, int pre) {
    depth[u] = depth[pre] + 1;
    dp[u][0] = pre;
    // 在DFS过程中初始化dp
    for (int j = 1; (1 << j) < depth[u]; ++j)
        dp[u][j] = dp[dp[u][j - 1]][j - 1];
    for (int i = head[u]; i; i = G[i].next)
        if (G[i].v != pre)
            dfs(G[i].v, u);
}

int doubly(int u, int v) {
    if (depth[u] < depth[v])
        swap(u, v);
    // 将u上移至与v同深度
    for (int j = 20; j >= 0; --j)
        if (depth[u] - (1 << j) >= depth[v])
            u = dp[u][j];
    if (u == v)
        return u;
    // u和v同时上移至LCA
    for (int j = 20; j >= 0; --j)
        if (dp[u][j] != dp[v][j])
            u = dp[u][j], v = dp[v][j];
    // 再往上移动一步
    return dp[u][0];
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    // clock_t xxx = clock();
    cin >> n >> m >> s;
    int u, v;
    for (int i = 1; i <= n - 1; ++i) {
        u = read(), v = read();
        add_edge(u, v);
        add_edge(v, u);
    }
    dfs(s, 0);
    for (int i = 0; i < m; ++i) {
        u = read(), v = read();
        printf("%d\n", doubly(u, v));
        // cout << doubly(u, v) << endl;
    }
    // clock_t zzz = clock();
    // cout << zzz - xxx;
    return 0;
}