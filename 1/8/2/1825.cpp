#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <string>
using namespace std;
typedef long long ll;

struct Node {
    int x, y, t;
    Node() {}
    Node(int _x, int _y, int _t) : x(_x), y(_y), t(_t) {}
};

const int maxn = 305;
int n, m, s, t;
string a[maxn];
int door[30];
map<int, int> magic;
int dir[4][2] = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
bool vis[maxn][maxn] = { false };

bool valid(int x, int y) {
    if (x < 0 || y < 0 || x >= n || y >= m)
        return false;
    if (vis[x][y])
        return false;
    return a[x][y] != '#';
}

void bfs() {
    queue<Node> q;
    q.push(Node(s, t, 0));
    vis[s][t] = true;
    while (q.size()) {
        Node nd = q.front();
        q.pop();
        if (a[nd.x][nd.y] == '=') {
            cout << nd.t;
            return;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = nd.x + dir[i][0], ny = nd.y + dir[i][1];
            if (valid(nx, ny)) {
                vis[nx][ny] = true;
                if (a[nx][ny] >= 'A' && a[nx][ny] <= 'Z') {
                    int tmp = magic[nx * 1000 + ny];
                    nx = tmp / 1000, ny = tmp % 1000;
                }
                q.push(Node(nx, ny, nd.t + 1));
            }
        }
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    memset(door, 0xff, sizeof(door));
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        for (int j = 0; j < m; ++j) {
            if (a[i][j] == '@')
                s = i, t = j;
            if (a[i][j] >= 'A' && a[i][j] <= 'Z') {
                int idx = a[i][j] - 'A';
                if (door[idx] == -1)
                    door[idx] = i * 1000 + j;
                else {
                    magic[door[idx]] = i * 1000 + j;
                    magic[i * 1000 + j] = door[idx];
                }
            }
        }
    }
    bfs();
    return 0;
}