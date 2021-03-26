#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

const int max_size = 26, maxn = 2e5 + 10;
int n, id[maxn], cnt = 0;
char s[maxn * 10];

struct Trie {
    // count表示该单词的个数，若只作为前缀则个数为0
    int ch[maxn][max_size], index, count[maxn];
    int fail[maxn], inDegree[maxn], ans[maxn];
    Trie() {
        memset(ch, 0, sizeof(ch));
        memset(count, 0, sizeof(count));
        memset(fail, 0, sizeof(fail));
        memset(ans, 0, sizeof(ans));
        memset(inDegree, 0, sizeof(inDegree));
        // 0-虚拟根节点，1-实际根节点
        for (int i = 0; i < max_size; ++i)
            ch[0][i] = 1;
        fail[1] = 0;
        index = 2;
    }

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
        id[cnt] = u;
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
                    fail[v] = ch[f][i];
                    // 入度加1
                    ++inDegree[fail[v]];
                    q.push(v);
                } else
                    v = ch[f][i];
            }
        }
    }

    void ac_auto(char* s) {
        int len = strlen(s), u = 1;
        for (int i = 0; i < len; ++i) {
            u = ch[u][s[i] - 'a'];
            ++ans[u];
        }
    }

    void topo() {
        queue<int> q;
        for (int i = 1; i <= index; ++i)
            if (inDegree[i] == 0)
                q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            int f = fail[u];
            ans[f] += ans[u];
            --inDegree[f];
            if (inDegree[f] == 0)
                q.push(f);
        }
    }
} trie;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d", &n);
    while (n--) {
        scanf("%s", s);
        trie.insert(s);
        ++cnt;
    }
    trie.build_fail();
    scanf("%s", s);
    trie.ac_auto(s);
    trie.topo();
    for (int i = 0; i < cnt; ++i)
        printf("%d\n", trie.ans[id[i]]);
    return 0;
}