#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 70;
int n, a[maxn], Next[maxn];
int tot = 0, aaa = 0;
bool vis[maxn] = { false };

inline int read() {
    int x = 0, sign = 1;
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

// sum表示已有的和，start表示当前访问的位置
bool dfs(int targ, int start, int sum) {
    ++aaa;
    // 凑到了
    if (sum == targ)
        return dfs(targ, 0, 0);
    // 凑多了、凑完了还没凑到
    if (sum > targ || start >= n)
        return false;
    bool noLeft = true;
    for (int i = start; i < n; ++i) {
        if (!vis[i]) {
            noLeft = false;
            vis[i] = true;
            // 找到下一个数
            bool flag = dfs(targ, i + 1, sum + a[i]);
            vis[i] = false;
            if (flag)
                return true;
            // 最重要的剪枝，一根木棍的第一部分必为剩余未组合的最长短棍
            if (sum + a[i] == targ || sum == 0)
                return false;
            i = Next[i];
        }
    }
    return noLeft && sum == 0;
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i) {
        a[i] = read();
        if (a[i] > 50)
            --n, --i;
        else
            tot += a[i];
    }
    sort(a, a + n, greater<int>());
    for (int i = n - 2; i >= 0; --i)
        if (a[i] == a[i + 1])
            Next[i] = Next[i + 1];
        else
            Next[i] = i;
    for (int i = a[0]; i <= tot; ++i) {
        // 寻找每个可能的答案
        if (tot % i == 0) {
            if (dfs(i, 0, 0)) {
                cout << i;
                break;
            }
        }
    }
    cout << endl << aaa;
    return 0;
}