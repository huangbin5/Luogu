#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

/**
 * sum = C(n-1,0)*a[0] + C(n-1,1)*a[1] + ... + C(n-1,n-1)*a[n-1]
 */
const int maxn = 15;
int n, s, a[maxn];
bool used[maxn] = { false };

int fac(int r) {
    if (r < 2)
        return 1;
    int ret = 1;
    for (int i = 2; i <= r; ++i)
        ret *= i;
    return ret;
}

int c(int r1, int r2) { return fac(r1) / fac(r2) / fac(r1 - r2); }

bool dfs(int idx, int sum) {
    if (idx > n || sum > s)
        return false;
    if (idx == n && sum == s) {
        for (int i = 0; i < n; ++i)
            cout << a[i] << " ";
        return true;
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            a[idx] = i;
            used[i] = true;
            if (dfs(idx + 1, sum + c(n - 1, idx) * a[idx]))
                return true;
            used[i] = false;
        }
    }
    return false;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> s;
    dfs(0, 0);
    return 0;
}