#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxm = 1005, maxn = 1e6 + 5;
int m, n, cnt[maxn] = { 0 };
bool prime[maxn] = { false };

void init() {
    for (int i = 2; i <= n; ++i) {
        cnt[i] = cnt[i - 1];
        if (!prime[i]) {
            ++cnt[i];
            for (int j = i + i; j <= n; j += i)
                prime[j] = true;
        }
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> m >> n;
    init();
    int l, r;
    for (int i = 0; i < m; ++i) {
        cin >> l >> r;
        if (l < 1 || l > n || r < 1 || r > n)
            cout << "Crossing the line" << endl;
        else if (l > r)
            cout << 0 << endl;
        else
            cout << cnt[r] - cnt[l - 1] << endl;
    }
    return 0;
}