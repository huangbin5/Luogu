#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

void handle(int n, int k) {
    if (n == 0) {
        cout << 0;
        return;
    }
    ll a = 1;
    if (k == 1) {
        while (a < n)
            a <<= 1;
        cout << a - n;
    } else {
        while ((a << 1) < n)
            a <<= 1;
        handle(n - a, k - 1);
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    ll n, k;
    cin >> n >> k;
    handle(n, k);
    return 0;
}