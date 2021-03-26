#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

struct Node {
    int x, y, t;
    Node() {}
    Node(int _x, int _y, int _t) : x(_x), y(_y), t(_t) {}
};

const int N = 300, maxn = 305;
int m, t[maxn][maxn];
int dir[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
bool danger[maxn][maxn] = { false }, vis[maxn][maxn];

bool valid(int x, int y) {
    if (x < 0 || y < 0)
        return false;
    return true;
}

void set_danger(int x, int y, int tm) {
    danger[x][y] = true;
    t[x][y] = min(t[x][y], tm);
    for (int i = 0; i < 4; ++i) {
        int nx = x + dir[i][0], ny = y + dir[i][1];
        if (valid(nx, ny)) {
            danger[nx][ny] = true;
            t[nx][ny] = min(t[nx][ny], tm);
        }
    }
}

bool valid(int x, int y, int tm) {
    if (!valid(x, y))
        return false;
    if (vis[x][y])
        return false;
    return tm < t[x][y];
}

bool bfs() {
    queue<Node> q;
    q.push(Node(0, 0, 0));
    vis[0][0] = true;
    while (q.size()) {
        Node nd = q.front();
        q.pop();
        // 到达安全点
        if (!danger[nd.x][nd.y]) {
            cout << nd.t << endl;
            return true;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = nd.x + dir[i][0], ny = nd.y + dir[i][1], nt = nd.t + 1;
            if (valid(nx, ny, nt)) {
                vis[nx][ny] = true;
                q.push(Node(nx, ny, nt));
            }
        }
    }
    return false;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    memset(t, 0x3f, sizeof(t));
    cin >> m;
    int x, y, tmp;
    for (int i = 0; i < m; ++i) {
        cin >> x >> y >> tmp;
        set_danger(x, y, tmp);
    }
    if (!bfs())
        cout << -1 << endl;
    return 0;
}