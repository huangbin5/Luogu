#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1005;
int v, n, c[maxn], w[maxn], a[maxn], dp[maxn], best = 0;

void zeroOnePack(int cost, int weight) {
    for (int j = v; j >= cost; --j)
        dp[j] = max(dp[j], dp[j - cost] + weight);
}

void completePack(int cost, int weight) {
    for (int j = cost; j <= v; ++j)
        dp[j] = max(dp[j], dp[j - cost] + weight);
}

void multiplePack(int cost, int weight, int amount) {
    if (cost * amount >= v)
        completePack(cost, weight);
    else {
        int coe = 1;
        while (amount > 0) {
            int tmp = min(coe, amount);
            zeroOnePack(tmp * cost, tmp * weight);
            amount -= coe;
            coe <<= 1;
        }
    }
}

void mixedPack(int cost, int weight, int amount) {
    // 用0来表示无数件
    if (amount == 0)
        completePack(cost, weight);
    else if (amount == 1)
        zeroOnePack(cost, weight);
    else
        multiplePack(cost, weight, amount);
}

// cur表示当前遍历的物品，curV表示已用体积，curW表示已有价值
void dfsPack(int cur, int curV, int curW) {
    if (curV > v)
        return;
    if (cur > n) {
        best = max(best, curW);
        return;
    }
    dfsPack(cur + 1, curV, curW);
    dfsPack(cur + 1, curV + c[cur], curW + w[cur]);
}

int main() {
#define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    for (int i = 1; i <= n; ++i)
        mixedPack(c[i], w[i], a[i]);
    return 0;
}