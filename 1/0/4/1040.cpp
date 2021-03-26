#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

/**
 * 状态：
 * dp[i][j]表示由节点i~j构成的子树的最大加分，整棵树的最大加分就是dp[1, n]
 * root[i][j]表示由节点i~j构成最大加分子树时所选的根
 * 状态转移：
 * dp[i][j] = max{dp[i][k - 1] * dp[k + 1][j] + dp[k][k]}
 * 其中dp[k][k] = score[k]
 */
const int maxn = 35;
int n, score[maxn];
ll dp[maxn][maxn] = { 0 }, root[maxn][maxn] = { 0 };

void preOrder(int i, int j) {
    if (i > j)
        return;
    cout << root[i][j] << " ";
    preOrder(i, root[i][j] - 1);
    preOrder(root[i][j] + 1, j);
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    // 空树加分为1，叶节点加分为得分
    for (int i = 1; i <= n; ++i) {
        cin >> score[i];
        dp[i][i] = score[i];
        root[i][i] = i;
        // 只可能用到dp[i][i - 1]而不可能用到dp[i][i - 2]
        dp[i][i-1]=1;
        // 以下做法是错误的，漏掉了dp[1][0] = 1
        // for (int j = 1; j < i; ++j)
        //     dp[i][j] = 1;
    }
    for (int span = 1; span < n; ++span)
        // 计算dp[i][i + span]
        for (int i = 1, j; (j = i + span) <= n; ++i)
            // 遍历每个根
            for (int k = i; k <= j; ++k) {
                ll tmp = dp[i][k - 1] * dp[k + 1][j] + dp[k][k];
                if (tmp > dp[i][j]) {
                    dp[i][j] = tmp;
                    root[i][j] = k;
                }
            }
    cout << dp[1][n] << endl;
    preOrder(1, n);
    return 0;
}