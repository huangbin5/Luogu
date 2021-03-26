#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 55;
int n, nLeft, t;
int G[maxn][maxn] = { 0 }, school[maxn], home[maxn];
// 二分图匹配的节点对
int match[maxn * 2];
bool vis[maxn * 2];

bool dfs(int u) {
    for (int v = 1; v <= n; ++v)
        if ((G[u][v] || u == v) && school[v] && !vis[v + n]) {
            // v不在当前交错路中，则将v加入交错路
            vis[v + n] = true;
            // 如果v就是非饱和点，或者通过交错路找到了非饱和点，说明找到了增广路
            if (!match[v + n] || dfs(match[v + n])) {
                // 则替换增广路中的匹配边，扩大匹配
                match[v + n] = u, match[u] = v + n;
                return true;
            }
        }
    // 找不到匹配的节点
    return false;
}

bool hungarian() {
    memset(match, 0, sizeof(match));
    for (int u = 1; u <= n; ++u) {
        if ((!school[u] || !home[u]) && !match[u]) {
            memset(vis, false, sizeof(vis));
            // 寻找u的匹配节点
            if (!dfs(u))
                return false;
        }
    }
    return true;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> t;
    while (t--) {
        cin >> n;
        for (int u = 1; u <= n; ++u)
            cin >> school[u];
        for (int u = 1; u <= n; ++u)
            cin >> home[u];
        for (int u = 1; u <= n; ++u)
            for (int v = 1; v <= n; ++v)
                cin >> G[u][v];
        if (hungarian())
            cout << "^_^" << endl;
        else
            cout << "T_T" << endl;
    }
    return 0;
}