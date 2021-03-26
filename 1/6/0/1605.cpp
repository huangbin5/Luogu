#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 6;
int n, m, t, board[maxn][maxn] = { 0 }, sx, sy, fx, fy, ans = 0;
struct Coord {
    int x, y;
    Coord() {}
    Coord(int _x, int _y)
        : x(_x)
        , y(_y) {}
};
const Coord direction[4] = { { -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 } };

bool valid(int x, int y) {
    if (x > 0 && x <= n && y > 0 && y <= m)
        return true;
    return false;
}

void dfs(int x, int y) {
    if (x == fx && y == fy) {
        ++ans;
        return;
    }
    board[x][y] = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + direction[i].x, ny = y + direction[i].y;
        if (valid(nx, ny) && !board[nx][ny])
            dfs(nx, ny);
    }
    board[x][y] = 0;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m >> t >> sx >> sy >> fx >> fy;
    int x, y;
    for (int i = 0; i < t; ++i) {
        cin >> x >> y;
        board[x][y] = 1;
    }
    dfs(sx, sy);
    cout << ans;
    return 0;
}