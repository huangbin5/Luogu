#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
#define nx (x + xx[i])
#define ny (y + yy[i])

const int maxn = 505;
int n, m, h[maxn][maxn];
bool vis[maxn][maxn] = { false };
int s[maxn][maxn], t[maxn][maxn], xx[4] = { -1, 1, 0, 0 }, yy[4] = { 0, 0, -1, 1 };

void init() {
    memset(s, 0x3f, sizeof(s));
    memset(t, 0xff, sizeof(t));
    for (int i = 0; i < m; ++i)
        s[n - 1][i] = t[n - 1][i] = i;
}

bool valid(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m)
        return true;
    return false;
}

void dfs(int x, int y) {
    vis[x][y] = true;
    for (int i = 0; i < 4; ++i)
        if (valid(nx, ny) && h[x][y] > h[nx][ny]) {
            if (!vis[nx][ny])
                dfs(nx, ny);
            s[x][y] = min(s[x][y], s[nx][ny]);
            t[x][y] = max(t[x][y], t[nx][ny]);
        }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    init();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> h[i][j];
    for (int i = 0; i < m; ++i)
        if (!vis[0][i])
            dfs(0, i);
    int cnt = 0;
    for (int i = 0; i < m; ++i)
        if (!vis[n - 1][i])
            ++cnt;
    if (cnt) {
        cout << 0 << endl << cnt;
        return 0;
    }
    int left = 0, right = 0;
    while (left < m) {
        for (int i = 0; i < m; ++i)
            if (s[0][i] <= left)
                right = max(right, t[0][i]);
        ++cnt;
        left = right + 1;
    }
    cout << 1 << endl << cnt;
    return 0;
}