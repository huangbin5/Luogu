#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 55;
// 是否有障碍
bool board[maxn][maxn] = { false };
int n, m, fx, fy;
// 记忆化，4个方向分别为↑→↓←
bool exist[maxn][maxn][4] = { false };
struct Element {
    int x, y, direction, cnt;
    Element() {}
    Element(int _x, int _y, int _direction, int _cnt)
        : x(_x)
        , y(_y)
        , direction(_direction)
        , cnt(_cnt) {}
};
Element s;
queue<Element> q;

bool handle(int nx, int ny, int nd, int cnt) {
    // 非法路径
    if (nx <= 0 || nx >= n || ny <= 0 || ny >= m || board[nx][ny])
        return false;
    if (!exist[nx][ny][nd]) {
        exist[nx][ny][nd] = true;
        q.push(Element(nx, ny, nd, cnt + 1));
    }
    return true;
}

void bfs() {
    q.push(s);
    exist[s.x][s.y][s.direction] = true;
    while (!q.empty()) {
        Element ele = q.front();
        q.pop();
        if (ele.x == fx && ele.y == fy) {
            cout << ele.cnt;
            return;
        }
        // 向左转
        int nx = ele.x, ny = ele.y, nd = (ele.direction + 3) % 4;
        handle(nx, ny, nd, ele.cnt);
        // 向右转
        nd = (ele.direction + 1) % 4;
        handle(nx, ny, nd, ele.cnt);
        // 向前
        nd = ele.direction;
        for (int i = 1; i <= 3; ++i) {
            if (nd == 0)
                --nx;
            else if (nd == 1)
                ++ny;
            else if (nd == 2)
                ++nx;
            else
                --ny;
            // 不能经过非法路径
            if (!handle(nx, ny, nd, ele.cnt))
                break;
        }
    }
    cout << "-1";
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    int tmp;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j) {
            cin >> tmp;
            if (tmp)
                board[i - 1][j - 1] = board[i - 1][j] = board[i][j - 1] = board[i][j] = true;
        }
    char direct;
    cin >> s.x >> s.y >> fx >> fy >> direct;
    if (direct == 'N')
        s.direction = 0;
    else if (direct == 'E')
        s.direction = 1;
    else if (direct == 'S')
        s.direction = 2;
    else
        s.direction = 3;
    bfs();
    return 0;
}