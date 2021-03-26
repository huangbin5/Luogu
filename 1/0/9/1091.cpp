#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, height[maxn], dp1[maxn] = { 0 }, dp2[maxn] = { 0 };

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> height[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            if (height[i] > height[j])
                dp1[i] = max(dp1[i], dp1[j]);
        ++dp1[i];
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - 1; j > i; --j)
            if (height[i] > height[j])
                dp2[i] = max(dp2[i], dp2[j]);
        ++dp2[i];
    }
    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans = max(ans, dp1[i] + dp2[i] - 1);
    cout << n - ans;
    return 0;
}