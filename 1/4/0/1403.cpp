#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

ll n, ans = 0;

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    // 对于left~right之间的每个i，n/i都相等
    for (int left = 1, right; left <= n; left = right + 1) {
        right = n / (n / left);
        ans += (n / left) * (right - left + 1);
    }
    cout << ans;
    return 0;
}