#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

struct Node {
    string s;
    int id, cnt;
    bool operator<(const Node& a) const {
        if (cnt != a.cnt)
            return cnt > a.cnt;
        return id < a.id;
    }
} node[155];
int cnt = 0;

const int max_size = 26, maxn = 150 * 70 + 10;
struct Trie {
    // count表示该单词的个数，若只作为前缀则个数为0
    int ch[maxn][max_size], index, count[maxn], id[maxn];
    int fail[maxn];
    Trie() {
        memset(ch, 0, sizeof(ch));
        memset(count, 0, sizeof(count));
        memset(fail, 0, sizeof(fail));
        memset(id, 0, sizeof(id));
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
        id[u] = cnt;
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
                    while (f && !ch[f][i])
                        f = fail[f];
                    // 将fail[v]置为fail[u]的子节点
                    fail[v] = ch[f][i];
                    q.push(v);
                } else
                    v = ch[f][i];
            }
        }
    }

    int ac_auto(char* s) {
        int len = strlen(s), u = 1;
        for (int i = 0; i < len; ++i) {
            int v = s[i] - 'a';
            while (u && !ch[u][v])
                u = fail[u];
            // 完成一个字符，往下继续
            u = ch[u][v];
            // 统计fail路径上的字符串数，直到1号root
            for (int j = u; j > 1; j = fail[j])
                if (count[j])
                    ++node[id[j]].cnt;
        }
    }
};

int n;
char s[1000005];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    while (scanf("%d", &n) && n) {
        cnt = 0;
        Trie trie;
        while (n--) {
            scanf("%s", s);
            trie.insert(s);
            node[cnt].s = string(s);
            node[cnt].id = cnt;
            node[cnt++].cnt = 0;
        }
        trie.build_fail();
        scanf("%s", s);
        trie.ac_auto(s);
        sort(node, node + cnt);
        int ans = node[0].cnt;
        printf("%d\n", ans);
        for (int i = 0; i < cnt; ++i) {
            if (ans != node[i].cnt)
                break;
            printf("%s\n", node[i].s.c_str());
        }
    }
    return 0;
}