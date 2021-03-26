#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1000005;
char s1[maxn], s2[maxn];

int* build_next(char* p) {
    size_t m = strlen(p), j = 0;
    int* next = new int[m];
    int t = next[0] = -1;
    while (j < m - 1) {
        if (t < 0 || p[j] == p[t]) {
            ++t, ++j;
            next[j] = t;
        } else
            t = next[t];
    }
    return next;
}
// 根据next数组进行匹配
int kmp(char* p, char* t) {
    int* next = build_next(p);
    int n = strlen(t), i = 0;
    int m = strlen(p), j = 0;
    while (i < n && j < m) {
        if (j < 0 || t[i] == p[j])
            ++i, ++j;
        else
            j = next[j];
        if (j == m) {
            printf("%d\n", i - j);
            j = next[m - 1];
            --i;
        }
    }
    return i - j;
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%s%s", s1, s2);
    kmp(s2, s1);
    return 0;
}