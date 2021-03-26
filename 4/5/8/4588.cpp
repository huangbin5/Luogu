#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 100005;
int t, n, MOD, in[maxn];
ll c[maxn];

struct Node {
    int l, r;
    ll prod;
} seg[maxn << 2];

void build(int p, int l, int r) {
    seg[p].l = l, seg[p].r = r;
    seg[p].prod = 1;
    if (l == r)
        return;
    int lc = p << 1, rc = lc | 1, mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
}

void set(int p, int r, int v) {
    if (seg[p].l == seg[p].r) {
        seg[p].prod = v;
        return;
    }
    int lc = p << 1, rc = lc | 1;
    if (r <= seg[lc].r)
        set(lc, r, v);
    if (r >= seg[rc].l)
        set(rc, r, v);
    seg[p].prod = (seg[lc].prod * seg[rc].prod) % MOD;
}

ll prod(int p, int r) {
    if (1 <= seg[p].l && seg[p].r <= r)
        return seg[p].prod;
    int lc = p << 1, rc = lc | 1;
    ll ans = 1;
    if (1 <= seg[lc].r)
        ans = (ans * prod(lc, r)) % MOD;
    if (r >= seg[rc].l)
        ans = (ans * prod(rc, r)) % MOD;
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d", &t);
    ll a, b;
    while (t--) {
        scanf("%d%d", &n, &MOD);
        build(1, 1, n);
        for (int i = 1; i <= n; ++i) {
            scanf("%lld%lld", &a, &b);
            a == 1 ? set(1, i, b % MOD) : set(1, b, 1);
            printf("%lld\n", prod(1, i));
        }
    }
    return 0;
}