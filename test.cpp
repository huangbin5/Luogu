#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const double pi = acos(-1.0);
const int maxn = 10, maxm = 10, INF = 0x3f3f3f3f;

#define DEBUG
#define SAMPLE
int main() {
#ifdef DEBUG
#ifndef SAMPLE
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
#endif
#ifdef SAMPLE
    // freopen("d:\\.in", "r", stdin);
    freopen("d:\\.in", "w", stdout);
#endif
    srand((unsigned int)time(NULL));
    int n = rand(), m = rand();
    while (n < 1 || m < 1)
        n = rand(), m = rand();
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; ++i)
        printf("%d ", rand());
    printf("\n");
    int l, r;
    for (int i = 0; i < m; ++i) {
        l = rand(), r = rand();
        while (l < 1 || l > n || r < 1 || r > n)
            l = rand(), r = rand();
        printf("%d %d\n", min(l, r), max(l, r));
    }
#ifndef DEBUG
#ifndef SAMPLE
    system("pause");
#endif
#endif
    return 0;
}