#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
// #define DEBUG

/**
 * 圈内的0肯定不会和边界的0连通
 */
const int maxn = 30;
int n, board[maxn][maxn];
bool flag[maxn][maxn] = { false };
struct Coord {
    int x, y;
    Coord() {}
    Coord(int _x, int _y)
        : x(_x)
        , y(_y) {}
    Coord operator+(Coord& coord) { return Coord(x + coord.x, y + coord.y); }
};
Coord direction[4] = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };
queue<Coord> q;

bool valid(Coord coord) {
    int x = coord.x, y = coord.y;
    if (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == 0 && !flag[x][y])
        return true;
    return false;
}

void bfs(Coord cur) {
    q.push(cur);
    while (!q.empty()) {
        cur = q.front();
        q.pop();
        flag[cur.x][cur.y] = true;
        for (int i = 0; i < 4; ++i)
            if (valid(cur + direction[i]))
                q.push(cur + direction[i]);
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> board[i][j];
    // 只要广度优先搜索边界上的0即可
    for (int i = 0; i < n; ++i) {
        // 上
        if (board[0][i] == 0 && !flag[0][i])
            bfs(Coord(0, i));
        // 下
        if (board[n - 1][i] == 0 && !flag[n - 1][i])
            bfs(Coord(n - 1, i));
        // 左
        if (board[i][0] == 0 && !flag[i][0])
            bfs(Coord(i, 0));
        // 右
        if (board[i][n - 1] == 0 && !flag[i][n - 1])
            bfs(Coord(i, n - 1));
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            if (board[i][j] == 0 && !flag[i][j])
                cout << 2 << " ";
            else
                cout << board[i][j] << " ";
        cout << endl;
    }
    return 0;
}