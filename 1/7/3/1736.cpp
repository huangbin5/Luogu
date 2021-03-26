#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const short maxn = 2505;
short n, m, a[maxn][maxn], ans = 0;
// up、left、right分别记录上面、左边、右边的1距离的位置
short u[maxn][maxn] = { 0 }, l[maxn][maxn] = { 0 }, r[maxn][maxn] = { 0 };
// dp1[i][j]表示以(i, j)为右下角的最大主对角线矩阵，dp2[i][j]表示左下角副对角线
short dp1[maxn][maxn] = { 0 }, dp2[maxn][maxn];

inline short read() {
    short x = 0, sign = 1;
    char c = getchar();
    // 符号
    for (; c > '9' || c < '0'; c = getchar())
        if (c == '-')
            sign = -1;
    // 多位数字
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    return x * sign;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            a[i][j] = read();
    for (int i = 1; i <= n; ++i) {
        int left = 0;
        for (int right = 1; right <= m; ++right)
            if (a[i][right] == 1) {
                l[i][right] = r[i][left] = right - left;
                left = right;
            }
        r[i][left] = m + 1 - left;
    }
    for (int j = 1; j <= m; ++j)
        for (int up = 0, down = 1; down <= n; ++down)
            if (a[down][j] == 1) {
                u[down][j] = down - up;
                up = down;
            }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            if (a[i][j] == 1) {
                dp1[i][j] = min(min(l[i][j], u[i][j]), (short)(dp1[i - 1][j - 1] + 1));
                ans = max(ans, dp1[i][j]);
            }
        for (int j = m; j >= 1; --j)
            if (a[i][j] == 1) {
                dp2[i][j] = min(min(r[i][j], u[i][j]), (short)(dp2[i - 1][j + 1] + 1));
                ans = max(ans, dp2[i][j]);
            }
    }
    cout << ans;
    return 0;
}