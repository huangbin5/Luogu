#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 1100;
int n;
char pic[maxn][2 * maxn];

// 图像的大小为2^n * 2^(n+1)
void draw(int x, int y, int lev) {
    if (lev == 1) {
        pic[x][y - 1] = pic[x + 1][y - 2] = '/';
        pic[x][y] = pic[x + 1][y + 1] = '\\';
        pic[x + 1][y - 1] = pic[x + 1][y] = '_';
        return;
    }
    draw(x, y, lev - 1);
    int wid = (1 << (lev - 1));
    draw(x + wid, y - wid, lev - 1);
    draw(x + wid, y + wid, lev - 1);
}

int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < (1 << (n + 1)); ++j)
            pic[i][j] = ' ';
        pic[i][1 << (n + 1)] = '\0';
    }
    draw(0, 1 << n, n);
    for (int i = 0; i < (1 << n); ++i)
        printf("%s\n", pic[i]);
    return 0;
}