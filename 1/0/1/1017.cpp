#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e4;
int n, radix, len = 0, ans[maxn];

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> radix;
    cout << n << "=";
    // 进制转换：除基取余
    while (n) {
        // 商
        int tmp = ceil(n * 1.0 / radix);
        // 余数
        ans[len++] = n - radix * tmp;
        n = tmp;
    }
    for (int i = len - 1; i >= 0; --i)
        if (ans[i] > 9)
            cout << (char)('A' + ans[i] - 10);
        else
            cout << ans[i];
    cout << "(base" << radix << ")";
    return 0;
}