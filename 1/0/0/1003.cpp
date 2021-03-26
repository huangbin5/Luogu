#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int MAXN = 10005;
int n, qx, qy;
struct Carpet {
    int x, y, w, h;
    Carpet() {}
    Carpet(int _x, int _y, int _w, int _h)
        : x(_x)
        , y(_y)
        , w(_w)
        , h(_h) {}
};
Carpet carpet[MAXN];

bool in(int index) {
    if (qx >= carpet[index].x && qx <= carpet[index].x + carpet[index].w && qy >= carpet[index].y
        && qy <= carpet[index].y + carpet[index].h)
        return true;
    return false;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d%d", &carpet[i].x, &carpet[i].y, &carpet[i].w, &carpet[i].h);
    scanf("%d%d", &qx, &qy);
    for (int i = n; i > 0; --i) {
        if (in(i)) {
            cout << i << endl;
            return 0;
        }
    }
    cout << -1 << endl;
    return 0;
}