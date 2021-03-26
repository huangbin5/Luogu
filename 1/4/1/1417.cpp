#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Node {
    int a, b, c;
    Node(){};
};

const int maxn = 55, maxv = 100005;
int t, n;
ll dp[maxn][maxv] = { 0 }, ans = 0;
Node node[maxn];

bool cmp(Node& i, Node& j) { return i.c * j.b < j.c * i.b; }

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> t >> n;
    for (int i = 1; i <= n; ++i)
        cin >> node[i].a;
    for (int i = 1; i <= n; ++i)
        cin >> node[i].b;
    for (int i = 1; i <= n; ++i)
        cin >> node[i].c;
    sort(node + 1, node + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= t; ++j) {
            if (j < node[i].c)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - node[i].c] + (ll)node[i].a - (ll)j * node[i].b);
            ans = max(ans, dp[i][j]);
        }
    cout << ans;
    return 0;
}