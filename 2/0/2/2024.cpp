#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 5e4 + 5;
int n, k, up[maxn * 3], ans = 0;

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

void init() {
    for (int i = 1; i <= n * 3; ++i)
        up[i] = i;
}

int find(int x) {
    if (x == up[x])
        return x;
    return up[x] = find(up[x]);
}

void merge(int x, int y) { up[find(x)] = find(y); }

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> k;
    init();
    int t, x, y;
    for (int i = 0; i < k; ++i) {
        t = read(), x = read(), y = read();
        if (x > n || y > n) {
            ++ans;
            continue;
        }
        if (t == 1) {
            if (find(x) == find(y + n) || find(x + n) == find(y))
                ++ans;
            else {
                merge(x, y);
                merge(x + n, y + n);
                merge(x + 2 * n, y + 2 * n);
            }
        } else {
            if (find(x) == find(y) || find(x + n) == find(y))
                ++ans;
            else {
                merge(x, y + n);
                merge(x + n, y + 2 * n);
                merge(x + 2 * n, y);
            }
        }
    }
    cout << ans;
    return 0;
}