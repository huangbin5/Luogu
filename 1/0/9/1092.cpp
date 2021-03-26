#include <cstdio>
#include <iostream>
#include <map>
#include <string>
using namespace std;
typedef long long ll;
// #define DEBUG

int n;
string s[3];
int num[3][26];
bool used[26] = { false };
int order[26], trans[26];

void init() {
    for (int i = 0; i < n; ++i)
        trans[i] = -1;
    int idx = 0;
    // 从低位到高位的顺序遍历
    for (int j = n - 1; j >= 0; --j)
        for (int i = 0; i < 3; ++i) {
            num[i][j] = s[i][j] - 'A';
            if (!used[num[i][j]]) {
                order[idx++] = num[i][j];
                used[num[i][j]] = true;
            }
        }
    for (int i = 0; i < n; ++i)
        used[i] = false;
}

bool check() {
    // 最高位不能有进位
    if (trans[num[0][0]] + trans[num[1][0]] >= n)
        return false;
    for (int i = 0; i < n; ++i) {
        int a = trans[num[0][i]], b = trans[num[1][i]], c = trans[num[2][i]];
        // 还有数不确定
        if (a == -1 || b == -1 || c == -1)
            continue;
        if ((a + b) % n != c && (a + b + 1) % n != c)
            return false;
    }
    return true;
}

bool verify() {
    for (int i = n - 1, x = 0; i >= 0; --i) {
        int a = trans[num[0][i]], b = trans[num[1][i]], c = trans[num[2][i]];
        if ((a + b + x) % n != c)
            return false;
        x = (a + b + x) / n;
    }
    return true;
}

bool dfs(int idx) {
    /**
     * 超级重要：如果从0 ~ n-1递增遍历，会非常非常慢
     */
    for (int i = n - 1; i >= 0; --i) {
        if (!used[i]) {
            trans[order[idx]] = i;
            used[i] = true;
            if (idx == n - 1 && verify())
                return true;
            if (idx < n - 1 && check() && dfs(idx + 1))
                return true;
            used[i] = false;
            trans[order[idx]] = -1;
        }
    }
    return false;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> s[0] >> s[1] >> s[2];
    init();
    dfs(0);
    for (int i = 0; i < n; ++i)
        cout << trans[i] << " ";
    return 0;
}