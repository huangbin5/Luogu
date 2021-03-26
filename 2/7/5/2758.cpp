#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 2005;
char s1[maxn], s2[maxn];
int len1, len2, dp[maxn][maxn] = { 0 };

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%s%s", s1 + 1, s2 + 1);
    len1 = strlen(s1 + 1), len2 = strlen(s2 + 1);
    for (int i = 1; i <= len1; ++i)
        dp[i][0] = i;
    for (int j = 1; j <= len2; ++j)
        dp[0][j] = j;
    for (int i = 1; i <= len1; ++i)
        for (int j = 1; j <= len2; ++j)
            if (s1[i] == s2[j])
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]) + 1, dp[i - 1][j - 1]);
            else
                dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
    printf("%d", dp[len1][len2]);
    return 0;
}