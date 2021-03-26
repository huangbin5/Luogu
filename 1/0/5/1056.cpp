#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int MAXN = 1005;
int M, N, K, L, D;
struct Stat {
    int num, cnt, flag;
    Stat() {
        cnt = 0;
        flag = 0;
    }
};
Stat horizontal[MAXN], vertical[MAXN];

void init() {
    for (int i = 0; i < MAXN; ++i) {
        horizontal[i].num = i;
        vertical[i].num = i;
    }
}

bool sortByCnt(Stat& a, Stat& b) { return a.cnt > b.cnt; }

bool sortByNum(Stat& a, Stat& b) {
    if (a.flag == b.flag)
        return a.num < b.num;
    return a.flag > b.flag;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    init();
    scanf("%d%d%d%d%d", &M, &N, &K, &L, &D);
    int a, b, c, d;
    for (int i = 0; i < D; ++i) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        if (a == c)
            vertical[min(b, d)].cnt++;
        if (b == d)
            horizontal[min(a, c)].cnt++;
    }
    sort(horizontal, horizontal + M, sortByCnt);
    sort(vertical, vertical + N, sortByCnt);
    for (int i = 0; i < K; ++i)
        horizontal[i].flag = 1;
    for (int i = 0; i < L; ++i)
        vertical[i].flag = 1;
    sort(horizontal, horizontal + M, sortByNum);
    sort(vertical, vertical + N, sortByNum);
    for (int i = 0; i < K; ++i) {
        if (i == K - 1)
            cout << horizontal[i].num << endl;
        else
            cout << horizontal[i].num << " ";
    }
    for (int i = 0; i < L; ++i) {
        if (i == L - 1)
            cout << vertical[i].num << endl;
        else
            cout << vertical[i].num << " ";
    }
    return 0;
}