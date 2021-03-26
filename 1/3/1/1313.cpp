#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxk = 1005, maxa = 1000005, MOD = 10007;
int k, n, m, a, b, C[maxk][maxk];

void getC() {
    for (int i = 0; i <= k; ++i) {
        C[i][0] = C[i][i] = 1;
    }
    for (int i = 2; i <= k; ++i) {
        for (int j = 1; j <= i / 2; ++j) {
            C[i][i - j] = C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
        }
    }
}

int quickPower(int p, int q) {
    int ans = 1;
    while (q) {
        if (q & 1)
            ans = (ans * p) % MOD;
        p = (p * p) % MOD;
        q >>= 1;
    }
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> a >> b >> k >> n >> m;
    getC();
    cout << ((C[k][n] * quickPower(a % MOD, n)) % MOD * quickPower(b % MOD, m)) % MOD;
    return 0;
}