#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 100005;
const int mod = 100003;
int n, k, ans[maxn] = { 0 };

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> k;
    ans[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = i - 1; j >= 0 && j >= i - k; --j)
            ans[i] = (ans[i] + ans[j]) % mod;
    cout << ans[n];
    return 0;
}