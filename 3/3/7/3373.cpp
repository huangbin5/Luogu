#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;
int n, m, MOD, a[maxn];

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

struct Node {
    int l, r;
    ll data, add, mul;
    Node() { add = 0, mul = 1; }
} seg[4 * maxn];

// 建树
void build(int p, int l, int r) {
    seg[p].l = l, seg[p].r = r;
    // 叶节点
    if (l == r) {
        seg[p].data = a[l];
        return;
    }
    int lc = p << 1, rc = lc + 1, mid = (l + r) >> 1;
    // 递归建子树
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg[p].data = (seg[lc].data + seg[rc].data) % MOD;
}

// 下推标记
void push_down(int p) {
    int lc = p << 1, rc = lc + 1;
    if (seg[p].mul != 1) {
        seg[lc].data = seg[lc].data * seg[p].mul % MOD;
        seg[lc].add = seg[lc].add * seg[p].mul % MOD;
        seg[lc].mul = seg[lc].mul * seg[p].mul % MOD;
        seg[rc].data = seg[rc].data * seg[p].mul % MOD;
        seg[rc].add = seg[rc].add * seg[p].mul % MOD;
        seg[rc].mul = seg[rc].mul * seg[p].mul % MOD;
        seg[p].mul = 1;
    }
    if (seg[p].add) {
        // 更新子节点
        seg[lc].data = (seg[lc].data + seg[p].add * (seg[lc].r - seg[lc].l + 1) % MOD) % MOD;
        seg[rc].data = (seg[rc].data + seg[p].add * (seg[rc].r - seg[rc].l + 1) % MOD) % MOD;
        seg[lc].add = (seg[lc].add + seg[p].add) % MOD;
        seg[rc].add = (seg[rc].add + seg[p].add) % MOD;
        // 清除标记
        seg[p].add = 0;
    }
}

// 区间修改
void add(int p, int l, int r, int v) {
    // 节点p在修改区间的内部
    if (l <= seg[p].l && seg[p].r <= r) {
        seg[p].data = (seg[p].data + v * (seg[p].r - seg[p].l + 1) % MOD) % MOD;
        seg[p].add = (seg[p].add + v) % MOD;
        return;
    }
    push_down(p);
    int lc = p << 1, rc = lc + 1;
    // 涉及到了左孩子
    if (l <= seg[lc].r)
        add(lc, l, r, v);
    // 涉及到了右孩子
    if (r >= seg[rc].l)
        add(rc, l, r, v);
    seg[p].data = (seg[lc].data + seg[rc].data) % MOD;
}

void mul(int p, int l, int r, int v) {
    if (l <= seg[p].l && seg[p].r <= r) {
        seg[p].data = seg[p].data * v % MOD;
        seg[p].mul = seg[p].mul * v % MOD;
        seg[p].add = seg[p].add * v % MOD;
        return;
    }
    push_down(p);
    int lc = p << 1, rc = lc + 1;
    if (l <= seg[lc].r)
        mul(lc, l, r, v);
    if (r >= seg[rc].l)
        mul(rc, l, r, v);
    seg[p].data = (seg[lc].data + seg[rc].data) % MOD;
}

// 区间查询
ll sum(int p, int l, int r) {
    if (l <= seg[p].l && seg[p].r <= r)
        return seg[p].data;
    push_down(p);
    int lc = p << 1, rc = lc + 1;
    ll ans = 0;
    if (l <= seg[lc].r)
        ans = (ans + sum(lc, l, r)) % MOD;
    if (r >= seg[rc].l)
        ans = (ans + sum(rc, l, r)) % MOD;
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    n = read(), m = read(), MOD = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    build(1, 1, n);
    int t, l, r, v;
    while (m--) {
        t = read(), l = read(), r = read();
        if (t == 3)
            printf("%lld\n", sum(1, l, r));
        else {
            v = read();
            t == 1 ? mul(1, l, r, v) : add(1, l, r, v);
        }
    }
    return 0;
}