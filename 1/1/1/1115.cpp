#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 200000, INF = 10000;
int n;

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    int sum = 0, ans = -INF, a;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        sum += a;
        ans = max(sum, ans);
        if (sum < 0)
            sum = 0;
    }
    cout << ans;
    return 0;
}