#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

const int maxn = 205;
int n, f, t, num[maxn];
bool vis[maxn] = { false };

struct Node {
    int floor, cnt;
    Node(){};
    Node(int _floor, int _cnt)
        : floor(_floor)
        , cnt(_cnt) {}
};

void bfs() {
    queue<Node> q;
    q.push(Node(f, 0));
    vis[f] = true;
    while (!q.empty()) {
        Node u = q.front();
        q.pop();
        if (u.floor == t) {
            cout << u.cnt;
            return;
        }
        int v = u.floor - num[u.floor];
        if (v > 0 && !vis[v]) {
            q.push(Node(v, u.cnt + 1));
            vis[v] = true;
        }
        v = u.floor + num[u.floor];
        if (v <= n && !vis[v]) {
            q.push(Node(v, u.cnt + 1));
            vis[v] = true;
        }
    }
    cout << -1;
}

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> f >> t;
    for (int i = 1; i <= n; ++i)
        cin >> num[i];
    bfs();
    return 0;
}