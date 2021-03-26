#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int maxn = 505;
struct Cord {
    double x, y;
    Cord() {}
    Cord(int _x, int _y) : x(_x), y(_y) {}
} cord[maxn];
struct Edge {
    int u, v;
    double d;
    Edge() {}
    Edge(int _u, int _v, double _d) : u(_u), v(_v), d(_d) {}
    bool operator<(const Edge& tmp) const { return d < tmp.d; }
} edge[maxn * maxn];

int n, m = 0, p;
int up[maxn];
vector<pair<int, int>> sele;

void init() {
    for (int i = 1; i <= n; ++i)
        up[i] = i;
}

int find(int x) {
    if (x == up[x])
        return x;
    return up[x] = find(up[x]);
}

void kruskal() {
    init();
    sort(edge, edge + m);
    int edgeNum = 0;
    for (int i = 1; i <= m; ++i) {
        Edge e = edge[i];
        int uu = find(e.u), vv = find(e.v);
        // 不构成环就加入
        if (uu != vv) {
            up[uu] = vv;
            ++edgeNum;
            sele.push_back(make_pair(e.u, e.v));
            if (edgeNum == n - p) {
                cout << fixed << setprecision(2) << e.d;
                return;
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
    cin >> p >> n;
    for (int u = 1; u <= n; ++u) {
        cin >> cord[u].x >> cord[u].y;
        for (int v = 1; v < u; ++v) {
            double d = hypot(cord[u].x - cord[v].x, cord[u].y - cord[v].y);
            edge[m++] = Edge(u, v, d);
            edge[m++] = Edge(v, u, d);
        }
    }
    kruskal();
    return 0;
}