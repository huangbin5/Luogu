#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Wood {
    int length, width;
    Wood() {}
    bool operator<(const Wood& a) {
        if (length != a.length)
            return length > a.length;
        return width > a.width;
    }
};

const int maxn = 5005;
int n, dp[maxn] = { 0 }, ans = 0;
Wood wood[maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> wood[i].length >> wood[i].width;
    sort(wood, wood + n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j)
            if (wood[i].width > wood[j].width)
                dp[i] = max(dp[i], dp[j]);
        ++dp[i];
        ans = max(ans, dp[i]);
    }
    cout << ans;
    return 0;
}