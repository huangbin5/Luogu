#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 10005, maxm = 200005;
int n, m, up[maxn], index;

void init() {
    index = n;
    for (int i = 1; i <= n; ++i)
        up[i] = ++index;
    for (int i = n + 1; i <= 2 * n; ++i)
        up[i] = i;
}

int find(int x) {
    if (x == up[x])
        return x;
    return up[x] = find(up[x]);
}

void merge(int x,int y){
    up[find(x)] = find(y);
}

int del(int x) {
    up[x] = ++index;
    up[index] = index;
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    char cmd[10];
    int u, v;
    for (int i = 0; i < m; ++i) {
        scanf("%s%d%d", &u, &v);
        if(cmd[0]=='C')merge(u,v);
    }
    return 0;
}