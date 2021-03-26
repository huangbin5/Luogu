#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 1005, maxm = 100005;
int n, m;
// board: 输入的迷宫
// flag: 与第几组数据连通（从1开始）
// ans: 第几组数据的答案（从1开始）
string board[maxn];
int flag[maxn][maxn] = { 0 }, ans[maxm] = { 0 };
struct Coord {
    int x, y;
    Coord() {}
    Coord(int _x, int _y)
        : x(_x)
        , y(_y) {}
    Coord operator+(Coord& coord) { return Coord(x + coord.x, y + coord.y); }
};
queue<Coord> q;
Coord direction[4] = { { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };

bool check(Coord coord, char v) {
    int x = coord.x, y = coord.y;
    if (x >= 0 && x < n && y >= 0 && y < n && !flag[x][y] && board[x][y] != v)
        return true;
    return false;
}

void bfs(int x, int y, int idx) {
    int cnt = 1;
    q.push(Coord(x, y));
    flag[x][y] = idx;
    while (!q.empty()) {
        Coord coord = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            Coord newCoord = coord + direction[i];
            if (check(newCoord, board[coord.x][coord.y])) {
                ++cnt;
                q.push(newCoord);
                flag[newCoord.x][newCoord.y] = idx;
            }
        }
    }
    ans[idx] = cnt;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> board[i];
    int x, y;
    for (int i = 1; i <= m; ++i) {
        cin >> x >> y;
        --x;
        --y;
        if (flag[x][y])
            ans[i] = ans[flag[x][y]];
        else
            bfs(x, y, i);
    }
    for (int i = 1; i <= m; ++i)
        cout << ans[i] << endl;
    return 0;
}