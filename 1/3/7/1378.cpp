#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Point {
    int x, y;
    double r, rr;
    Point() {}
};

const double PI = acos(-1.0);
const int maxn = 10;
int x, xx, y, yy, n;
Point point[maxn];
double dist[maxn][maxn], ans = 0;
bool vis[maxn] = { false };

void cacul(int idx) {
    Point& p = point[idx];
    p.r = min(min(abs(p.x - x), abs(p.x - xx)), min(abs(p.y - y), abs(p.y - yy)));
    for (int i = 0; i < idx; ++i)
        dist[idx][i] = dist[i][idx] = hypot(p.x - point[i].x, p.y - point[i].y);
}

void dfs(int cnt, double area) {
    if (cnt == n) {
        ans = max(ans, area);
        return;
    }
    // 滴下一滴油
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) {
            // 算出油的半径
            point[i].rr = point[i].r;
            for (int j = 0; j < n; ++j)
                if (vis[j])
                    point[i].rr = min(point[i].rr, max(0.0, dist[i][j] - point[j].rr));
            vis[i] = true;
            dfs(cnt + 1, area + PI * point[i].rr * point[i].rr);
            vis[i] = false;
        }
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> x >> y >> xx >> yy;
    for (int i = 0; i < n; ++i) {
        cin >> point[i].x >> point[i].y;
        if (!((point[i].x < x) ^ (point[i].x < xx) && (point[i].y < y) ^ (point[i].y < yy)))
            --i, --n;
        cacul(i);
    }
    dfs(0, 0);
    // 不加int过不了#6#7
    cout << (int)(round)(abs(x - xx) * abs(y - yy) - ans);
    return 0;
}