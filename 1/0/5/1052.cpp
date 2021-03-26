#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105, mind = 91;
int L, m, M, n, num[maxn] = { 0 };

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> L >> m >> M >> n;
    if (m == M) {
        int tmp, ans = 0;
        for (int i = 0; i < n; ++i) {
            cin >> tmp;
            if (tmp % m == 0)
                ++ans;
        }
        cout << ans;
    } else {
        for (int i = 1; i <= n; ++i)
            cin >> num[i];
        sort(num + 1, num + n + 1);
        // sum是上一个石子压缩后的位置
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            if (num[i] - num[i - 1] > mind)
                sum += mind;
            else
                sum += num[i] - num[i - 1];
            num[i - 1] = sum;
        }
        // 压缩后的路径长度
        L = sum + 15;
        // dp[i]表示刚好到i时需要踩的最少石子数，
        int* dp = new int[L];
        // 初始化dp数组
        dp[0] = 0;
        for (int i = 1; i < L; ++i)
            dp[i] = maxn;
        int idx = 0;
        for (int i = 1; i < L; ++i) {
            for (int j = i - M; j >= 0 && j <= i - m; ++j)
                dp[i] = min(dp[i], dp[j]);
            if (num[idx] == i) {
                ++dp[i];
                ++idx;
            }
        }
        int ans = maxn;
        for (int i = L - 1; i >= sum; --i)
            ans = min(ans, dp[i]);
        cout << ans;
    }
    return 0;
}