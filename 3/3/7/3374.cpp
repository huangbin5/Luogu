#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 5e5 + 5;
int n, m, a[maxn], c[maxn];

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

inline int lowbit(int x) { return x & (-x); }

// a[x] += v
void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += v;
}

int sum(int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

// sum(x, y)
int sum(int x, int y) { return sum(y) - sum(x - 1); }

void init() {
    for (int i = 1; i <= n; ++i) {
        a[i] = read();
        // 由a[i]建树
        add(i, a[i]);
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
    for (int i = 0; i < m; ++i) {
        t = read(), l = read(), r = read();
        if (t == 1)
            add(l, r);
        else
            printf("%d\n", sum(l, r));
    }
    return 0;
}