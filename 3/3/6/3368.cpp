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

void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += v;
}

// a[x, y] += v
void add(int x, int y, int v) {
    add(x, v);
    add(y + 1, -v);
}

// a[x]
int sum(int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

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
    int t, x, y, v;
    for (int i = 0; i < m; ++i) {
        t = read(), x = read();
        if (t == 1) {
            y = read(), v = read();
            add(x, y, v);
        } else
            printf("%d\n", sum(x));
    }
    return 0;
}