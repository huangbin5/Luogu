#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 160, INF = 0x3f3f3f3f;
struct Cord {
    double x, y;
    Cord() {}
    Cord(double _x, double _y) : x(_x), y(_y) {}
} cord[maxn];

int n;
double dis[maxn][maxn] = { 0 }, far[maxn] = { 0 }, ans = 0;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    // 输入点
    for (int u = 1; u <= n; ++u)
        cin >> cord[u].x >> cord[u].y;
    string m;
    // 输入边
    for (int u = 1; u <= n; ++u) {
        cin >> m;
        for (int v = 1; v <= n; ++v) {
            if (m[v - 1] == '1')
                dis[u][v] = dis[v][u] = hypot(cord[u].x - cord[v].x, cord[u].y - cord[v].y);
            else if (u != v)
                dis[u][v] = INF;
        }
    }
    // Floyd
    for (int k = 1; k <= n; ++k)
        for (int u = 1; u <= n; ++u)
            for (int v = 1; v <= n; ++v)
                if (dis[u][k] + dis[k][v] < dis[u][v])
                    dis[u][v] = dis[u][k] + dis[k][v];
    for (int u = 1; u <= n; ++u) {
        // 求出距离u最远但可以到达的距离
        for (int v = 1; v <= n; ++v)
            if (dis[u][v] != INF)
                far[u] = max(far[u], dis[u][v]);
        ans = max(ans, far[u]);
    }
    double radius = INF;
    for (int u = 1; u <= n; ++u)
        for (int v = 1; v <= n; ++v)
            if (dis[u][v] == INF)
                radius = min(radius, far[u] + far[v] + hypot(cord[u].x - cord[v].x, cord[u].y - cord[v].y));
    cout << fixed << setprecision(6) << max(ans, radius) << endl;
    return 0;
}