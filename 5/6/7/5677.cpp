#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const ll maxn = 3e5 + 5;
ll n, m, pn = 0, c[maxn] = { 0 }, ans = 0;

struct Data {
    ll v, i;
    bool operator<(const Data& b) { return v < b.v; }
} a[maxn];

struct Pair {
    ll u, v;
    bool operator<(const Pair& b) { return v < b.v; }
} pr[maxn << 1];

struct Ask {
    ll l, r, i;
    bool operator<(const Ask& b) { return r < b.r; }
} ask[maxn];

void add_pair(int x, int y) { pr[++pn] = { min(x, y), max(x, y) }; }

inline ll lowbit(ll x) { return x & (-x); }

void add(ll x) {
    for (ll i = x; i <= n; i += lowbit(i))
        c[i]++;
}

ll sum(ll x) {
    ll ans = 0;
    for (ll i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

// sum(x, y)
ll sum(ll x, ll y) { return sum(y) - sum(x - 1); }

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    // 输入n个数
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= n; ++i) {
        scanf("%lld", &a[i].v);
        a[i].i = i;
    }
    sort(a + 1, a + n + 1);
    // 找出所有配对
    add_pair(a[1].i, a[2].i);
    add_pair(a[n - 1].i, a[n].i);
    for (ll i = 2; i < n; ++i) {
        ll comp = (a[i].v - a[i - 1].v) - (a[i + 1].v - a[i].v);
        if (comp <= 0)
            add_pair(a[i - 1].i, a[i].i);
        if (comp >= 0)
            add_pair(a[i].i, a[i + 1].i);
    }
    sort(pr + 1, pr + pn + 1);
    // 输入询问
    for (ll i = 1; i <= m; ++i) {
        scanf("%lld%lld", &ask[i].l, &ask[i].r);
        ask[i].i = i;
    }
    sort(ask + 1, ask + m + 1);
    // 处理查询
    ll idx = 1;
    for (ll i = 1; i <= m; ++i) {
        while (idx <= pn && pr[idx].v <= ask[i].r)
            add(pr[idx++].u);
        ans += ask[i].i * sum(ask[i].l, ask[i].r);
    }
    printf("%lld", ans);
    return 0;
}