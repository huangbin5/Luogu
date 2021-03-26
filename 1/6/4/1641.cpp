#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 5, MOD = 20100403;
int n, m;

int ex_gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int g = ex_gcd(b, a % b, x, y);
    int tmp = x;
    x = y, y = tmp - a / b * y;
    return g;
}

int inverse(int a, int p) {
    int g, x, y;
    g = ex_gcd(a, p, x, y);
    if (g == 1)
        return (x % p + p) % p;
    else
        return -1;
}

ll fac(int a) {
    ll ans = 1;
    for (int i = 2; i <= a; ++i)
        ans = (ans * i) % MOD;
    return ans;
}

int C(int a, int b) {
    b = (fac(b) * fac(a - b)) % MOD;
    a = fac(a);
    int inv = inverse(b, MOD);
    return ((ll)a * inv) % MOD;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    cout << (C(n + m, m) - C(n + m, m - 1) + MOD) % MOD;
    return 0;
}