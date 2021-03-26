#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 50005;
ll n, m;
ll a[maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
        if (m == 0)
            cout << a[i] << " ";
    }
    for (int i = n - 1; i > 0; --i) {
        // i位数能构成的最多逆序对
        ll maxInverse = (ll)i * (i - 1) / 2;
        // 前n - i - 1位数不需要移动
        if (m > maxInverse) {
            ll firstChange = n - i - 1;
            // 直接输出前n - i - 1位
            for (int j = 0; j < firstChange; ++j)
                cout << a[j] << " ";
            // 输出第1位移动过的数字
            cout << a[firstChange + m - maxInverse] << " ";
            // 剩余的数倒序输出即可
            for (int j = n - 1; j >= firstChange; --j)
                if (j != firstChange + m - maxInverse)
                    cout << a[j] << " ";
            break;
        }
    }
    return 0;
}