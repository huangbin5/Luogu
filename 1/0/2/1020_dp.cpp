#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 100005;
// dp1和dp2分别为“最长不上升子序列”和“最长上升子序列”
int n = 0, height[maxn], dp1[maxn] = { 0 }, dp2[maxn] = { 0 }, ans1 = 0, ans2 = 0;

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    while (cin >> height[n + 1])
        ++n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j < i; ++j)
            if (height[i] <= height[j])
                dp1[i] = max(dp1[i], dp1[j]);
            else
                dp2[i] = max(dp2[i], dp2[j]);
        ++dp1[i];
        ans1 = max(ans1, dp1[i]);
        ++dp2[i];
        ans2 = max(ans2, dp2[i]);
    }
    cout << ans1 << endl << ans2;
    return 0;
}