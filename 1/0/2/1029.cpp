#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

int n, m, ans = 0;

int gcd(int a, int b) {
    if (a < b)
        return gcd(b, a);
    if (a % b == 0)
        return b;
    return gcd(b, a % b);
}

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> m >> n;
    if (n % m == 0) {
        for (int a = m; a <= n; a += m) {
            if (m * n % a)
                continue;
            int b = m * n / a;
            if (gcd(a, b) == m)
                ++ans;
        }
    }
    cout << ans;
    return 0;
}