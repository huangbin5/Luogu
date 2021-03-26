#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

const int max_size = 26, maxn = 1e6 + 10;
struct Trie {
    // count表示该单词的个数，若只作为前缀则个数为0
    int ch[maxn][max_size], index, count[maxn];
    int fail[maxn];
    Trie() {
        memset(ch, 0, sizeof(ch));
        memset(count, 0, sizeof(count));
        memset(fail, 0, sizeof(fail));
        // 0-虚拟根节点，1-实际根节点
        for (int i = 0; i < max_size; ++i)
            ch[0][i] = 1;
        fail[1] = 0;
        index = 2;
    }

    // 这里可以重复添加相同单词
    void insert(char* s) {
        // 从1号root开始
        int u = 1, len = strlen(s);
        for (int i = 0; i < len; ++i) {
            int v = s[i] - 'a';
            if (!ch[u][v])
                ch[u][v] = index++;
            u = ch[u][v];
        }
        ++count[u];
    }

    void build_fail() {
        queue<int> q;
        q.push(1);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < max_size; ++i) {
                int &v = ch[u][i], f = fail[u];
                if (v) {
                    // 将fail[v]置为fail[u]的子节点
                    fail[v] = ch[f][i];
                    q.push(v);
                } else
                    v = ch[f][i];
            }
        }
    }

    int ac_auto(char* s) {
        int len = strlen(s), u = 1, ans = 0;
        for (int i = 0; i < len; ++i) {
            // 完成一个字符，往下继续
            u = ch[u][s[i] - 'a'];
            // 统计fail路径上的字符串数，直到1号root
            for (int j = u; j > 1 && count[j] != -1; j = fail[j]) {
                ans += count[j];
                count[j] = -1;
            }
        }
        return ans;
    }
} trie;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    char s[maxn];
    while (n--) {
        scanf("%s", s);
        trie.insert(s);
    }
    trie.build_fail();
    scanf("%s", s);
    printf("%d", trie.ac_auto(s));
    return 0;
}