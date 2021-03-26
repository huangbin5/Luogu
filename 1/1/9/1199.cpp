#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 505;
int n, mq[maxn][maxn], maxmq = -1;
int sele[maxn] = { 0 };
bool vis[maxn][maxn] = { false };

// 我方从剩余可选组合中挑选出最大值
pair<int, int> sel_max() {
    pair<int, int> ans;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (sele[i] != -1 && sele[j] != -1 && (sele[i] & sele[j]) == 0 && mq[i][j] > mq[ans.first][ans.second])
                ans = make_pair(i, j);
    return ans;
}

// 敌方破坏我方的最好选择
int prevent() {
    pair<int, int> ans;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (sele[i] + sele[j] == 1 && mq[i][j] > mq[ans.first][ans.second])
                ans = make_pair(i, j);
    if (sele[ans.first] == 0)
        return ans.first;
    else
        return ans.second;
}

// 更新最大默契值
void update() {
    int p1 = -1, p2 = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            if (sele[i] == 1 && sele[j] == 1 && mq[i][j] > p1)
                p1 = mq[i][j];
            if (sele[i] == -1 && sele[j] == -1 && mq[i][j] > p2)
                p2 = mq[i][j];
        }
    // 先要保证能赢
    if (p1 > p2)
        maxmq = p1;
}

void dfs() {
    pair<int, int> next = sel_max();
    // 选将完成了
    if (next.first == 0) {
        update();
        return;
    }
    for (int i = 0; i < 2; ++i) {
        int j = i ? next.second : next.first;
        if (sele[j] == 0) {
            // 我方
            sele[j] = 1;
            // 敌方
            int pre = prevent();
            sele[pre] = -1;
            dfs();
            sele[pre] = 0;
            sele[j] = 0;
        }
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    mq[0][0] = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            cin >> mq[i][j];
    dfs();
    if (maxmq == -1)
        cout << 0;
    else
        cout << 1 << endl << maxmq;
    return 0;
}