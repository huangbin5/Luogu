#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;
int n, m, arr[maxn];
int dp[maxn][25];

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

// 这里dp存储的是最小的元素，也可以按实际要求存储最小值的下标
void init() {
    for (int i = 1; i <= n; ++i)
        dp[i][0] = arr[i];
    for (int j = 1; (1 << j) <= n; ++j)
        for (int i = 1; i + (1 << j) <= n + 1; ++i)
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}

int rmq(int l, int r) {
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1)
        ++k;
    return max(dp[l][k], dp[r - (1 << k) + 1][k]);
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        arr[i] = read();
    init();
    int l, r;
    for (int i = 0; i < m; ++i) {
        l = read(), r = read();
        printf("%d\n", rmq(l, r));
    }
    return 0;
}