#include <cstdio>
#include <iomanip>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 405;
int n, m;
struct Element {
    int x, y;
    Element() {}
    Element(int _x, int _y, int _cnt = 0)
        : x(_x)
        , y(_y) {}
    Element operator+(Element& e) { return Element(x + e.x, y + e.y); }
};
Element direction[8] = { { -1, -2 }, { -1, 2 }, { 1, -2 }, { 1, 2 }, { -2, -1 }, { -2, 1 }, { 2, -1 }, { 2, 1 } };
Element s;
queue<Element> q;
int cnt[maxn][maxn];

bool check(Element& e) {
    if (e.x >= 1 && e.x <= n && e.y >= 1 && e.y <= m && cnt[e.x][e.y] == -1)
        return true;
    return false;
}

void bfs() {
    cnt[s.x][s.y] = 0;
    q.push(s);
    while (!q.empty()) {
        Element ele = q.front();
        q.pop();
        for (int i = 0; i < 8; ++i) {
            Element ne = ele + direction[i];
            if (check(ne)) {
                cnt[ne.x][ne.y] = cnt[ele.x][ele.y] + 1;
                q.push(ne);
            }
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m >> s.x >> s.y;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cnt[i][j] = -1;
    bfs();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j)
            cout << left << setw(5) << cnt[i][j];
        cout << endl;
    }
    return 0;
}