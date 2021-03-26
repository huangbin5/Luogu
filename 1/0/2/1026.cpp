#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

const int maxn = 205, maxk = 41;
string s = " ", word[6];
// cnt[i][j]表示i~j之间单词的数量，dp[i][j]表示前i个字符分为j份时包含单词的最大总数
int p, n, cnt[maxn][maxn] = { 0 }, dp[maxn][maxk] = { 0 };

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> p;
    string tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        s += tmp;
    }
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> word[i];
    for (int j = s.size() - 1; j >= 1; --j)
        for (int i = j; i >= 1; --i) {
            cnt[i][j] = cnt[i + 1][j];
            for (int k = 0; k < n; ++k) {
                int pos = s.find(word[k], i);
                if (pos == i && pos + word[k].size() - 1 <= j) {
                    ++cnt[i][j];
                    break;
                }
            }
        }
    // dp[i][j] = max{dp[k][j-1] + cnt[k+1][i]}   k = j-1...i-1
    for (int i = 1; i < s.size(); ++i)
        for (int j = 1; j <= p && j <= i; ++j)
            for (int k = j - 1; k <= i - 1; ++k)
                dp[i][j] = max(dp[i][j], dp[k][j - 1] + cnt[k + 1][i]);
    cout << dp[s.size() - 1][p];
    return 0;
}