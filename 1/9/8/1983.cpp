#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int n, m, G[maxn][maxn] = { 0 };
int len[maxn] = { 0 }, ans = 0;

int dfs(int v) {
    if (!len[v]) {
        for (int u = 1; u <= n; ++u)
            if (G[u][v])
                len[v] = max(len[v], dfs(u));
        ++len[v];
        ans = max(ans, len[v]);
    }
    return len[v];
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    vector<int> vec;
    int cnt, num;
    for (int i = 0; i < m; ++i) {
        vec.clear();
        cin >> cnt;
        for (int j = 0; j < cnt; ++j) {
            cin >> num;
            vec.push_back(num);
        }
        for (int j = 1; j < vec.size(); ++j)
            for (int u = vec[j - 1] + 1; u < vec[j]; ++u)
                for (auto v : vec)
                    G[u][v] = 1;
    }
    for (int i = 1; i <= n; ++i)
        if (!len[i])
            dfs(i);
    cout << ans;
    return 0;
}