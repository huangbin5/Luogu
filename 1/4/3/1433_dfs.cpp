#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
#include <limits>
using namespace std;
typedef long long ll;
#define DEBUG

struct Coord {
    double x, y;
    Coord() {}
    Coord(double _x, double _y)
        : x(_x)
        , y(_y) {}
};

const int maxn = 20;
int n;
Coord cheese[maxn];
double distant[maxn][maxn];
bool used[maxn] = { false };
double ans = numeric_limits<double>::max();

void dfs(int cnt, int idx, double dis) {
    if (dis > ans)
        return;
    if (cnt == n) {
        ans = dis;
        return;
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            used[i] = true;
            dfs(cnt + 1, i, dis + distant[idx][i]);
            used[i] = false;
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\data.in", "r", stdin);
    freopen("d:\\data.out", "w", stdout);
#endif
    cheese[0] = { 0, 0 };
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> cheese[i].x >> cheese[i].y;
        for (int j = 0; j < i; ++j)
            distant[i][j] = distant[j][i] = hypot(cheese[i].x - cheese[j].x, cheese[i].y - cheese[j].y);
    }
    used[0] = true;
    dfs(0, 0, 0.0);
    used[0] = false;
    cout << fixed << setprecision(2) << ans;
    return 0;
}