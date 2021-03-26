#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Comod {
    int id, cost, weight, father, cnt, son[2];
    Comod() { cnt = son[0] = son[1] = 0; }
};

const int maxn = 32000, maxm = 60;
// n-总钱数，m-商品数
int n, m, dp[maxn] = { 0 };
Comod comod[maxm];

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        comod[i].id = i;
        cin >> comod[i].cost >> comod[i].weight >> comod[i].father;
        int father = comod[i].father;
        // 如果是附件
        if (father)
            comod[father].son[comod[father].cnt++] = i;
    }
    for (int i = 1; i <= m; ++i)
        // 主件才要处理，附件跟随主件处理
        if (comod[i].father == 0)
            for (int j = n; j >= 0; --j)
                for (int k = 0; k < (1 << comod[i].cnt); ++k) {
                    // 0-主件；1-主件+附件1；2-主件+附件2；3-主件+附件1+附件2
                    int cost = comod[i].cost, weight = comod[i].weight * comod[i].cost;
                    int son0 = comod[i].son[0], son1 = comod[i].son[1];
                    if (k & 1) {
                        cost += comod[son0].cost;
                        weight += comod[son0].weight * comod[son0].cost;
                    }
                    if (k & 2) {
                        cost += comod[son1].cost;
                        weight += comod[son1].weight * comod[son1].cost;
                    }
                    if (j >= cost)
                        dp[j] = max(dp[j], dp[j - cost] + weight);
                }
    cout << dp[n];
    return 0;
}