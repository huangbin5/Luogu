#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 25;
int m, n, k;
int earth[maxn][maxn];
struct Peanut {
    int num, x, y;
    Peanut(int _num, int _x, int _y)
        : num(_num)
        , x(_x)
        , y(_y) {}
};
vector<Peanut> order;
int totalTime = 0, preTime, ans = 0;

bool cmp(Peanut& a, Peanut& b) { return a.num > b.num; }

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &m, &n, &k);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            scanf("%d", &earth[i][j]);
            if (earth[i][j])
                order.push_back(Peanut(earth[i][j], i, j));
        }
    sort(order.begin(), order.end(), cmp);
    int preX = -1, preY = order[0].y;
    for (vector<Peanut>::iterator it = order.begin(); it != order.end(); ++it) {
        totalTime += (abs(it->x - preX) + abs(it->y - preY) + 1);
        if ((preTime = totalTime + it->x + 1) > k) {
            cout << ans;
            return 0;
        }
        ans += it->num;
        preX = it->x;
        preY = it->y;
    }
    cout << ans;
    return 0;
}