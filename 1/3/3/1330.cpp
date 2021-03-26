#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 10005;
int n, m, flag[maxn] = { 0 }, cnt[2], ans = 0;
vector<int> G[maxn];

bool dfs(int u, int color) {
    color == 1 ? ++cnt[1] : ++cnt[0];
    flag[u] = color;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (!flag[v]) {
            if (!dfs(v, -color))
                return false;
        } else if (flag[v] == color)
            return false;
    }
    return true;
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    int a, b;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    for (int u = 1; u <= n; ++u)
        if (!flag[u]) {
            cnt[0] = cnt[1] = 0;
            if (!dfs(u, 1)) {
                cout << "Impossible";
                return 0;
            }
            ans += min(cnt[0], cnt[1]);
        }
    cout << ans;
    return 0;
}