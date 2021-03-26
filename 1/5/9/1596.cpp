#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, m, ans = 0;
string a[maxn];
bool vis[maxn][maxn] = { 0 };
int direc[8][2] = { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 } };

bool valid(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= m)
        return false;
    return !vis[x][y] && a[x][y] == 'W';
}

void dfs(int x, int y) {
    vis[x][y] = true;
    for (int i = 0; i < 8; ++i) {
        int nx = x + direc[i][0], ny = y + direc[i][1];
        if (valid(nx, ny))
            dfs(nx, ny);
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (valid(i, j)) {
                ++ans;
                dfs(i, j);
            }
    cout << ans;
    return 0;
}