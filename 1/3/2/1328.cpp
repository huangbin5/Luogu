#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int MAXN = 205;
const int TABLE[5][5] = { { 0, 0, 1, 1, 0 }, { 1, 0, 0, 1, 0 }, { 0, 1, 0, 0, 1 }, { 0, 0, 1, 0, 1 }, { 1, 1, 0, 0, 0 } };
int n, na, nb;
int xa[MAXN], xb[MAXN];
int sa = 0, sb = 0;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &n, &na, &nb);
    for (int i = 0; i < na; ++i)
        scanf("%d", &xa[i]);
    for (int i = 0; i < nb; ++i)
        scanf("%d", &xb[i]);
    for (int i = 0; i < n; ++i) {
        sa += TABLE[xa[i % na]][xb[i % nb]];
        sb += TABLE[xb[i % nb]][xa[i % na]];
    }
    cout << sa << " " << sb << endl;
    return 0;
}