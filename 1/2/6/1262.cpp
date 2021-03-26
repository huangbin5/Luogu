#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 3005;
int n, money[maxn], sccMoney[maxn];
vector<int> edge[maxn];
int dTime[maxn], lowlink[maxn], scc[maxn];
int curTime = 0, sccNo = 0;
stack<int> s;
bool first[maxn];

void tarjan(int u) {
    // lowlink初始最高指向自己
    dTime[u] = lowlink[u] = ++curTime;
    s.push(u);
    for (int i = 0; i < edge[u].size(); ++i) {
        int v = edge[u][i];
        // 根据相邻节点的lowlink更新自己的lowlink
        if (!dTime[v]) {
            tarjan(v);
            lowlink[u] = min(lowlink[u], lowlink[v]);
        } else if (!scc[v])
            lowlink[u] = min(lowlink[u], lowlink[v]);
    }
    // lowlink[u] == dTime[u]，说明该节点是当前scc中最先发现的节点，由于scc中任意一点v都能达到u，故所有lowlink[v] == dTime[u]
    if (lowlink[u] == dTime[u]) {
        ++sccNo;
        for (;;) {
            int x = s.top();
            s.pop();
            scc[x] = sccNo;
            if (money[x] != -1)
                sccMoney[sccNo] = min(sccMoney[sccNo], money[x]);
            if (x == u)
                break;
        }
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    memset(money, 0xff, sizeof(money));
    memset(sccMoney, 0x3f, sizeof(sccMoney));
    cin >> n;
    int m, a, b;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a;
        cin >> money[a];
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a >> b;
        edge[a].push_back(b);
    }
    memset(scc, 0, sizeof(scc));
    memset(dTime, 0, sizeof(dTime));
    // 对每个可贿赂的节点求强连通分量
    for (int i = 1; i <= n; ++i)
        if (!dTime[i] && money[i] != -1)
            tarjan(i);
    // 如果还有没有遍历的节点说明不可达
    for (int i = 1; i <= n; ++i)
        if (!dTime[i]) {
            cout << "NO" << endl << i;
            return 0;
        }
    // 判断每个强连通分量是否有前驱
    memset(first, true, sizeof(first));
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < edge[i].size(); ++j)
            if (scc[i] != scc[edge[i][j]])
                first[scc[edge[i][j]]] = false;
    // 将所有没有前驱的强连通分量的费用加起来
    int ans = 0;
    for (int i = 1; i <= sccNo; ++i)
        if (first[i])
            ans += sccMoney[i];
    cout << "YES" << endl << ans;
    return 0;
}