#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 4e5 + 5, maxm = 2e5 + 5;
// const int maxn = 100, maxm = 100;
struct Edge {
    int v, next;
    Edge() {}
    Edge(int _v, int _next) : v(_v), next(_next) {}
} edge[maxm * 2];
int head[maxn];

int n, m, k, eNum = 0, up[maxn];
vector<int> attack;
stack<int> ans;
bool exist[maxn], root[maxn];

void add_edge(int u, int v) {
    edge[++eNum] = Edge(v, head[u]);
    head[u] = eNum;
}

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
    memset(root, true, sizeof(root));
    memset(exist, true, sizeof(exist));
}

int find(int x) {
    if (x == up[x])
        return x;
    return up[x] = find(up[x]);
}

void count() {
    for (int u = 1; u <= n; ++u)
        if (exist[u])
            for (int i = head[u]; i; i = edge[i].next) {
                int v = edge[i].v;
                if (exist[v]) {
                    int uu = find(u), vv = find(v);
                    if (uu != vv) {
                        up[vv] = uu;
                        root[vv] = false;
                    }
                }
            }
    int cnt = 0;
    for (int u = 1; u <= n; ++u)
        if (exist[u] && root[u])
            ++cnt;
    ans.push(cnt);
}

void fix(int u) {
    int cnt = ans.top() + 1;
    exist[u] = true;
    for (int i = head[u]; i; i = edge[i].next) {
        int v = edge[i].v;
        if (exist[v]) {
            int uu = find(u), vv = find(v);
            if (uu != vv) {
                up[vv] = uu;
                --cnt;
            }
        }
    }
    ans.push(cnt);
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    init();
    int u, v;
    for (int i = 0; i < m; ++i) {
        u = read(), v = read();
        add_edge(u + 1, v + 1);
        add_edge(v + 1, u + 1);
    }
    cin >> k;
    for (int i = 0; i < k; ++i) {
        u = read();
        attack.push_back(u + 1);
        exist[u + 1] = false;
    }
    count();
    for (int i = attack.size() - 1; i >= 0; --i)
        fix(attack[i]);
    while (!ans.empty()) {
        printf("%d\n", ans.top());
        ans.pop();
    }
    return 0;
}