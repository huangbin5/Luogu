#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 5;
int n = 0, m, MOD;

// 注意要开4倍空间
struct Node {
    int l, r;
    ll max;
} seg[maxn << 2];

// 建树
void build(int p, int l, int r) {
    seg[p].l = l, seg[p].r = r;
    // 叶节点
    if (l == r) {
        seg[p].max = 0;
        return;
    }
    int lc = p << 1, rc = lc | 1, mid = (l + r) >> 1;
    // 递归建左右子树
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

// 点修改
void set(int p, int x, ll v) {
    if (x == seg[p].l && seg[p].r == x) {
        seg[p].max = v;
        return;
    }
    int lc = p << 1, rc = lc | 1;
    if (x <= seg[lc].r)
        set(lc, x, v);
    else
        set(rc, x, v);
    seg[p].max = max(seg[lc].max, seg[rc].max);
}

// 区间查询
ll max(int p, int l, int r) {
    if (l <= seg[p].l && seg[p].r <= r)
        return seg[p].max;
    int lc = p << 1, rc = lc | 1;
    ll ans = 0x8000000000000000;
    if (l <= seg[lc].r)
        ans = max(ans, max(lc, l, r));
    if (r >= seg[rc].l)
        ans = max(ans, max(rc, l, r));
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d%d", &m, &MOD);
    build(1, 1, m);
    char op[5];
    ll v, pre = 0;
    while (m--) {
        scanf("%s%lld", op, &v);
        if (op[0] == 'Q')
            printf("%lld\n", pre = max(1, n - v + 1, n));
        else {
            ++n;
            set(1, n, (pre + v) % MOD);
        }
    }
    return 0;
}