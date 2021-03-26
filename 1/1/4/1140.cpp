#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

const int maxn = 105;
const int w[5][5]
    = { { 5, -1, -2, -1, -3 }, { -1, 5, -3, -2, -4 }, { -2, -3, 5, -2, -2 }, { -1, -2, -2, 5, -1 }, { -3, -4, -2, -1, 0 } };
int alen, blen, dp[maxn][maxn] = { 0 };
string a, b;

int id(char x) {
    switch (x) {
    case 'A':
        return 0;
    case 'C':
        return 1;
    case 'G':
        return 2;
    case 'T':
        return 3;
    default:
        return 4;
    }
}

int score(char x, char y) { return w[id(x)][id(y)]; }

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> alen >> a >> blen >> b;
    for (int i = 1; i <= a.size(); ++i)
        dp[i][0] = dp[i - 1][0] + score(a[i - 1], '-');
    for (int j = 1; j <= b.size(); ++j)
        dp[0][j] = dp[0][j - 1] + score('-', b[j - 1]);
    for (int i = 1; i <= a.size(); ++i)
        for (int j = 1; j <= b.size(); ++j)
            dp[i][j] = max(dp[i - 1][j - 1] + score(a[i - 1], b[j - 1]),
                max(dp[i - 1][j] + score(a[i - 1], '-'), dp[i][j - 1] + score('-', b[j - 1])));
    cout << dp[a.size()][b.size()];
    return 0;
}