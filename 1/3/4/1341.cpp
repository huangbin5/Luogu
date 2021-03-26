#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;
typedef long long ll;

const int maxn = 60;
int m, n = 0, G[maxn][maxn] = { 0 };
char dic[maxn * maxn][2];
set<char> st;
map<char, int> toInt;
char toChar[maxn];
int degree[maxn], odd = 0, origin = 0;
bool used[maxn] = { false }, vis[maxn][maxn] = { 0 };
string ans = "";

void dfs(int u) {
    used[u] = true;
    for (int v = 0; v < n; ++v)
        if (G[u][v] && !used[v])
            dfs(v);
}

void euler(int u) {
    for (int v = 0; v < n; ++v) {
        if (G[u][v] && !vis[u][v]) {
            vis[u][v] = 1;
            vis[v][u] = 1;
            euler(v);
        }
    }
    ans += toChar[u];
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> m;
    for (int i = 0; i < m; ++i) {
        getchar();
        getchar();
        dic[i][0] = getchar();
        st.insert(dic[i][0]);
        dic[i][1] = getchar();
        st.insert(dic[i][1]);
    }
    for (auto i : st) {
        toInt[i] = n;
        toChar[n++] = i;
    }
    // 构造图
    for (int i = 0; i < m; ++i) {
        int u = toInt[dic[i][0]], v = toInt[dic[i][1]];
        G[u][v] = G[v][u] = 1;
        ++degree[u];
        ++degree[v];
    }
    for (int i = n - 1; i >= 0; --i)
        if (degree[i] & 1) {
            ++odd;
            origin = i;
        }
    // 不满足欧拉环路的必要条件
    if (odd != 0 && odd != 2) {
        cout << "No Solution";
        return 0;
    }
    dfs(0);
    // 图不连通
    for (int i = 0; i < n; ++i)
        if (!used[i]) {
            cout << "No Solution";
            return 0;
        }
    euler(origin);
    reverse(ans.begin(), ans.end());
    cout << ans;
    return 0;
}