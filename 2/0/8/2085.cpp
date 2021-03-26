#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

struct Node {
    int u, v, ans;
    Node(int _u, int _v, int _ans) : u(_u), v(_v), ans(_ans) {}
    bool operator<(const Node& a) const { return ans > a.ans; }
};

const int maxn = 10005;
int n, m, a[maxn], b[maxn], c[maxn];
priority_queue<Node> pq;

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

int cacul(int u, int v) { return a[u] * v * v + b[u] * v + c[u]; }

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    n = read(), m = read();
    for (int i = 0; i < n; ++i)
        a[i] = read(), b[i] = read(), c[i] = read();
    for (int i = 0; i < n; ++i)
        pq.push(Node(i, 1, cacul(i, 1)));
    for (int i = 0; i < m; ++i) {
        Node node = pq.top();
        pq.pop();
        printf("%d ", node.ans);
        ++node.v;
        node.ans = cacul(node.u, node.v);
        pq.push(node);
    }
    return 0;
}