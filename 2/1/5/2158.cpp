#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 40005;
int n, ans, cnt[maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    if (n == 1) {
        cout << 0;
        return 0;
    }
    --n;
    ans = n * n + 2;
    for (int i = n; i >= 2; --i) {
        cnt[i] = (n / i) * (n / i);
        for (int j = i + i; j <= n; j += i)
            cnt[i] -= cnt[j];
        ans -= cnt[i];
    }
    cout << ans;
    return 0;
}