#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;

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
    ll data, tag;
} seg[4 * maxn];

int n, m, a[maxn];

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
    seg[p].data = seg[lc].data + seg[rc].data;
}

// 下推标记
void push_down(int p) {
    if (seg[p].tag) {
        int lc = p << 1, rc = lc + 1;
        // 更新子节点
        seg[lc].data += seg[p].tag * (seg[lc].r - seg[lc].l + 1);
        seg[rc].data += seg[p].tag * (seg[rc].r - seg[rc].l + 1);
        seg[lc].tag += seg[p].tag;
        seg[rc].tag += seg[p].tag;
        // 清除标记
        seg[p].tag = 0;
    }
}

// 区间修改
void add(int p, int l, int r, int v) {
    // 节点p在修改区间的内部
    if (l <= seg[p].l && seg[p].r <= r) {
        seg[p].data += (ll)v * (seg[p].r - seg[p].l + 1);
        seg[p].tag += v;
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
    seg[p].data = seg[lc].data + seg[rc].data;
}

// 区间查询
ll sum(int p, int l, int r) {
    if (l <= seg[p].l && seg[p].r <= r)
        return seg[p].data;
    push_down(p);
    int lc = p << 1, rc = lc + 1;
    ll ans = 0;
    if (l <= seg[lc].r)
        ans += sum(lc, l, r);
    if (r >= seg[rc].l)
        ans += sum(rc, l, r);
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    build(1, 1, n);
    int t, l, r, v;
    while (m--) {
        t = read(), l = read(), r = read();
        if (t == 1) {
            v = read();
            add(1, l, r, v);
        } else
            printf("%lld\n", sum(1, l, r));
    }
    return 0;
}