#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

struct Node {
    int u, v, sum;
    Node(int _u, int _v, int _sum) : u(_u), v(_v), sum(_sum) {}
    bool operator<(const Node& a) const { return sum > a.sum; }
};

const int maxn = 100005;
int n, a[maxn], b[maxn];
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

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    n = read();
    for (int i = 0; i < n; ++i)
        a[i] = read();
    for (int i = 0; i < n; ++i)
        b[i] = read();
    for (int i = 0; i < n; ++i)
        pq.push(Node(i, 0, a[i] + b[0]));
    for (int i = 0; i < n; ++i) {
        Node node = pq.top();
        pq.pop();
        printf("%d ", node.sum);
        ++node.v;
        node.sum = a[node.u] + b[node.v];
        pq.push(node);
    }
    return 0;
}