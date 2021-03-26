#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 50005;
int n, m;
vector<int> G[maxn];
int dTime[maxn], lowlink[maxn];
int dfsClock = 0, scc[maxn], sccNo = 0;
stack<int> s;
vector<int> vec, ans;

bool operator>(const vector<int>& a, const vector<int>& b) {
    if (a.size() != b.size())
        return a.size() > b.size();
    for (int i = 0; i < a.size(); ++i)
        if (a[i] != b[i])
            return a[i] < b[i];
    return false;
}

void dfs(int u) {
    // lowlink初始化为dTime
    dTime[u] = lowlink[u] = ++dfsClock;
    s.push(u);
    for (auto v : G[u]) {
        // 根据相邻节点的lowlink更新自己的lowlink
        if (!dTime[v]) {
            dfs(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (!scc[v])
            lowlink[u] = min(lowlink[u], lowlink[v]);
    }
    // 遍历完了当前SCC
    if (lowlink[u] == dTime[u]) {
        ++sccNo;
        vec.clear();
        for (;;) {
            int x = s.top();
            s.pop();
            vec.push_back(x);
            scc[x] = sccNo;
            if (x == u)
                break;
        }
        sort(vec.begin(), vec.end());
        if (vec > ans)
            ans = vec;
    }
}

void tarjan() {
    memset(dTime, 0, sizeof(dTime));
    memset(scc, 0, sizeof(scc));
    for (int i = 1; i <= n; ++i)
        if (!dTime[i])
            dfs(i);
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    int u, v, t;
    while (m--) {
        cin >> u >> v >> t;
        G[u].push_back(v);
        if (t == 2)
            G[v].push_back(u);
    }
    tarjan();
    cout << ans.size() << endl;
    for (auto i : ans)
        cout << i << " ";
    return 0;
}