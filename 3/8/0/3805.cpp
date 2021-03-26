#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 3e7;
char s[maxn];
int n = 0;

void read() {
    s[n++] = '#';
    char c;
    while ((c = getchar()) && 'a' <= c && c <= 'z') {
        s[n++] = c;
        s[n++] = '#';
    }
}

int longestPalindrome() {
    int sz = strlen(s), *len = new int[sz], middle = 0, right = 0;
    len[0] = 0;
    for (int i = 1; i < sz; ++i) {
        len[i] = i <= right ? min(len[2 * middle - i], right - i) : 0;
        // 往外延伸
        for (int l = i - len[i] - 1, r = i + len[i] + 1; l >= 0 && r < sz && s[l] == s[r]; --l, ++r)
            ++len[i];
        if (i + len[i] > right) {
            right = i + len[i];
            middle = i;
        }
    }
    int ans = 0;
    for (int i = 1; i < sz; ++i)
        if (len[i] > len[ans])
            ans = i;
    return len[ans];
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    read();
    printf("%d", longestPalindrome());
    return 0;
}