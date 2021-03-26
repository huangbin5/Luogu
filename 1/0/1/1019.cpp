#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 20;
int n, cnt[maxn] = { 0 }, ans = 0;
string word[maxn];
char startChar;
struct Candidate {
    int idx, len;
    Candidate() {}
    Candidate(int _idx, int _len)
        : idx(_idx)
        , len(_len) {}
};
vector<Candidate> cadidate[maxn];

int getCommonLen(string& a, string& b) {
    int len = min(a.size(), b.size());
    for (int i = 1; i <= len - 1; ++i)
        if (a.substr(a.size() - i) == b.substr(0, i))
            return i;
    return 0;
}

void getCandidate(int a, int b) {
    int tmp;
    if (tmp = getCommonLen(word[a], word[b]))
        cadidate[a].push_back(Candidate(b, tmp));
    if (a != b && (tmp = getCommonLen(word[b], word[a])))
        cadidate[b].push_back(Candidate(a, tmp));
}

void dfs(int idx, int len) {
    bool flag = false;
    for (int i = 0; i < cadidate[idx].size(); ++i) {
        Candidate next = cadidate[idx][i];
        if (cnt[next.idx] < 2) {
            flag = true;
            cnt[next.idx]++;
            dfs(next.idx, len + word[next.idx].size() - next.len);
            cnt[next.idx]--;
        }
    }
    if (!flag)
        ans = max(ans, len);
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> word[i];
        for (int j = 0; j <= i; ++j)
            getCandidate(i, j);
    }
    cin >> startChar;
    for (int i = 0; i < n; ++i)
        if (word[i][0] == startChar) {
            // 这里不要漏了计数
            cnt[i]++;
            dfs(i, word[i].size());
            cnt[i]--;
        }
    cout << ans;
    return 0;
}