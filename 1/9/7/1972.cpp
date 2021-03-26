#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

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

const int maxn = 1e6 + 5;
int n, m, a[maxn], cnt[maxn], c[maxn] = { 0 }, index[maxn] = { 0 }, aaa[maxn];

inline int lowbit(int x) { return x & (-x); }

// a[x] += v
void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += v;
}

int sum(int x) {
    int aaa = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        aaa += c[i];
    return aaa;
}

// sum(x, y)
int sum(int x, int y) { return sum(y) - sum(x - 1); }

struct Query {
    int l, r, id;
    bool operator<(const Query& q) const { return r < q.r; }
} query[maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    n = read();
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    m = read();
    for (int i = 1; i <= m; ++i) {
        query[i].l = read(), query[i].r = read();
        query[i].id = i;
    }
    sort(query + 1, query + m + 1);
    for (int i = 1; i <= m;) {
        int r = query[i].r;
        for (int j = query[i - 1].r + 1; j <= r; ++j) {
            if (index[a[j]])
                add(index[a[j]], -1);
            add(j, 1);
            index[a[j]] = j;
        }
        for (; r == query[i].r && i <= m; ++i) {
            int l = query[i].l;
            aaa[query[i].id] = sum(l, r);
        }
    }
    for (int i = 1; i <= m; ++i)
        printf("%d\n", aaa[i]);
    return 0;
}