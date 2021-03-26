#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    ll n, k, ans;
    cin >> n >> k;
    ans = k * n;
    for (int s = 1, t; s <= n; s = t + 1) {
        if (k / s)
            t = min(k / (k / s), n);
        else
            t = n;
        ans -= k / s * (s + t) * (t - s + 1) / 2;
    }
    cout << ans;
    return 0;
}