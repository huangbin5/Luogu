#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 25;
int n, k, a[maxn], ans = 0;

bool is_prime(int x) {
    int sqx = sqrt(x);
    for (int i = 2; i <= sqx; ++i)
        if (x % i == 0)
            return false;
    return true;
}

void dfs(int idx, int cnt, int sum) {
    if (cnt == k) {
        if (is_prime(sum))
            ++ans;
        return;
    }
    for (int i = idx + 1; cnt + n - i >= k; ++i)
        dfs(i, cnt + 1, sum + a[i]);
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> k;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; n - i >= k; ++i)
        dfs(i, 1, a[i]);
    cout << ans;
    return 0;
}