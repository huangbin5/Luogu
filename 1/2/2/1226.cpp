#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
#define DEBUG

ll a, b, n;

int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> a >> b >> n;
    cout << a << "^" << b << " mod " << n << "=";
    ll ans = 1;
    while (b) {
        if (b & 1)
            ans = (ans * a) % n;
        a = (a * a) % n;
        b >>= 1;
    }
    cout << ans % n;
    return 0;
}