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

const int maxn = 305;
int n, m;
vector<Edge> G[maxn];
int dis[maxn];
bool vis[maxn];

int prim(int s) {
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, false, sizeof(vis));
    dis[s] = 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int u = 0;
        for (int j = 1; j <= n; ++j)
            if (!vis[j] && dis[j] < dis[u])
                u = j;
        if (!u)
            return -1;
        vis[u] = true;
        ans = max(ans, dis[u]);
        for (auto e : G[u])
            if (e.d < dis[e.v])
                dis[e.v] = e.d;
    }
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    int u, v, d;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> d;
        G[u].push_back(Edge(v, d));
        G[v].push_back(Edge(u, d));
    }
    cout << n - 1 << " " << prim(1);
    return 0;
}