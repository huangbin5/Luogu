#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

/**
 * 末尾0是由因子2*因子5得来的，且1~n中因子2的个数一定比因子5的个数多
 * 因此对每个数去掉因子2和因子5再相乘，最后乘上多余的2只保留个位数即可
 */
int n, cnt = 0;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    int ans = 1;
    for (int i = 2; i <= n; ++i) {
        int m = i;
        // 去掉因子2和因子5
        while (m % 2 == 0)
            ++cnt, m /= 2;
        while (m % 5 == 0)
            --cnt, m /= 5;
        // 相乘保留个位数
        ans = ans * m % 10;
    }
    // 乘上多余的2
    for (int i = 0; i < cnt; ++i)
        ans = ans * 2 % 10;
    cout << ans;
    return 0;
}