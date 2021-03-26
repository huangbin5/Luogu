#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int score[9][9] = { { 6, 6, 6, 6, 6, 6, 6, 6, 6 }, { 6, 7, 7, 7, 7, 7, 7, 7, 6 }, { 6, 7, 8, 8, 8, 8, 8, 7, 6 },
    { 6, 7, 8, 9, 9, 9, 8, 7, 6 }, { 6, 7, 8, 9, 10, 9, 8, 7, 6 }, { 6, 7, 8, 9, 9, 9, 8, 7, 6 }, { 6, 7, 8, 8, 8, 8, 8, 7, 6 },
    { 6, 7, 7, 7, 7, 7, 7, 7, 6 }, { 6, 6, 6, 6, 6, 6, 6, 6, 6 } };
int board[9][9], ans = -1;
bool row[9][10] = { false }, col[9][10] = { false }, gon[9][10] = { false };

struct Pos {
    int r, n;
    Pos() {}
    Pos(int _r, int _n)
        : r(_r)
        , n(_n) {}
};
Pos pos[9];

bool cmp(Pos& a, Pos& b) { return a.n < b.n; }

void update() {
    int res = 0;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            res += board[i][j] * score[i][j];
    if (res > ans)
        ans = res;
}

void dfs(int n) {
    int r, c, g;
    // 获取下一个格子
    while (n < 81) {
        ++n;
        r = pos[n / 9].r;
        c = n % 9;
        g = r / 3 * 3 + c / 3;
        if (board[r][c] == 0)
            break;
    }
    // 全部填满了就更新最大分数
    if (n == 81) {
        update();
        return;
    }
    // 依次尝试填充1-9
    for (int i = 1; i <= 9; ++i) {
        if (!(row[r][i] || col[c][i] || gon[g][i])) {
            row[r][i] = true;
            col[c][i] = true;
            gon[g][i] = true;
            board[r][c] = i;
            dfs(n);
            board[r][c] = 0;
            row[r][i] = false;
            col[c][i] = false;
            gon[g][i] = false;
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\data.in", "r", stdin);
    freopen("d:\\data.out", "w", stdout);
#endif
    for (int i = 0; i < 9; ++i) {
        int n = 0;
        for (int j = 0; j < 9; ++j) {
            cin >> board[i][j];
            int num = board[i][j];
            if (num) {
                row[i][num] = true;
                col[j][num] = true;
                gon[i / 3 * 3 + j / 3][num] = true;
            } else
                ++n;
        }
        pos[i] = Pos(i, n);
    }
    sort(pos, pos + 9, cmp);
    dfs(-1);
    cout << ans;
    return 0;
}