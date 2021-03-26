#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Comod {
    int id, price, impor, main;
    Comod() {}
};

const int maxn = 32000, maxm = 60;
// n-总钱数，m-商品数
int n, m, dp[maxm][maxn] = { 0 };
Comod comod[maxm];

bool cmp(Comod& a, Comod& b) {
    int aid = a.main ? a.main : a.id, bid = b.main ? b.main : b.id;
    if (aid != bid)
        return aid < bid;
    return a.main < b.main;
}

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        comod[i].id = i;
        cin >> comod[i].price >> comod[i].impor >> comod[i].main;
    }
    sort(comod + 1, comod + m + 1, cmp);
    for (int i = 1; i <= m; ++i) {
        int minPrice = comod[i].price, addImpor = comod[i].price * comod[i].impor;
        // 如果是附件，则应该和主件绑定
        if (comod[i].main) {
            int main = comod[i - 1].main ? i - 2 : i - 1;
            minPrice += comod[main].price;
            addImpor += comod[main].price * comod[main].impor;
        }
        for (int j = n; j >= 0; --j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= minPrice) {
                // 如果是主件
                if (!comod[i].main)
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - minPrice] + addImpor);
                // 如果是第一个附件
                else if (!comod[i - 1].main)
                    dp[i][j] = max(dp[i][j], dp[i - 2][j - minPrice] + addImpor);
                // 如果是第二个附件
                else {
                    dp[i][j] = max(dp[i][j], dp[i - 3][j - minPrice] + addImpor);
                    // 如果买得起第一个附件
                    if (j - minPrice >= comod[i - 1].price)
                        dp[i][j] = max(dp[i][j],
                            dp[i - 3][j - minPrice - comod[i - 1].price] + addImpor + comod[i - 1].price * comod[i - 1].impor);
                }
            }
        }
    }
    cout << dp[m][n];
    return 0;
}