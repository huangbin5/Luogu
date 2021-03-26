#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 105;
int n, m, height[maxn][maxn], length[maxn][maxn] = { 0 }, ans = 0;
int direction[4][2] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

int dfs(int x, int y) {
    length[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + direction[i][0], ny = y + direction[i][1];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && height[nx][ny] < height[x][y])
            if (length[nx][ny])
                length[x][y] = max(length[x][y], length[nx][ny] + 1);
            else
                length[x][y] = max(length[x][y], dfs(nx, ny) + 1);
    }
    ans = max(ans, length[x][y]);
    return length[x][y];
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> height[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!length[i][j])
                dfs(i, j);
    cout << ans << endl;
    return 0;
}