#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;
int n, m;
ll a[maxn], c1[maxn], c2[maxn];

inline ll read() {
    ll x = 0, sign = 1;
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

inline int lowbit(int x) { return x & (-x); }

void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        c1[i] += v;
        // 注意是(x - 1)不是(i - 1)
        c2[i] += (x - 1) * v;
    }
}

// a[x, y] += v
void add(int x, int y, int v) {
    add(x, v);
    // 注意是-v
    add(y + 1, -v);
}

ll sum(int x) {
    ll ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += x * c1[i] - c2[i];
    return ans;
}

// sum(x, y)
ll sum(int x, int y) { return sum(y) - sum(x - 1); }

void init() {
    a[0] = 0;
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        // 差分建树
        add(i, a[i] - a[i - 1]);
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    n = read(), m = read();
    init();
    int t, l, r;
    ll v;
    while (m--) {
        t = read(), l = read(), r = read();
        if (t == 1) {
            v = read();
            add(l, r, v);
        } else
            printf("%lld\n", sum(l, r));
    }
    return 0;
}