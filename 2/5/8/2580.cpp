#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <string>
using namespace std;
typedef long long ll;

// 字母表的大小
const int max_size = 30, maxn = 5e5 + 5;
// 根节点编号为0
struct Trie {
    // ch[i][j]表示节点i的第j个字母存放的节点编号，若不存在则为0
    // count表示前缀(单词)出现的次数
    int ch[maxn][max_size], index, count[maxn];
    bool isWord[maxn], ask[maxn];
    Trie() {
        // 初始时只有根节点
        index = 1;
        memset(ch, 0, sizeof(ch));
        memset(isWord, false, sizeof(isWord));
        memset(count, 0, sizeof(count));
    }

    void insert(char* s) {
        int u = 0, len = strlen(s);
        for (int i = 0; i < len; ++i) {
            int v = s[i] - 'a';
            if (!ch[u][v])
                ch[u][v] = index++;
            u = ch[u][v];
        }
        // 如果单词尚未存在
        if (!isWord[u]) {
            isWord[u] = true;
            ask[u] = false;
            u = 0;
            // 更新沿途节点作为前缀出现的次数
            for (int i = 0; i < len; ++i) {
                int v = s[i] - 'a';
                u = ch[u][v];
                ++count[u];
            }
        }
    }

    void remove(char* s) {
        int u = 0, len = strlen(s);
        for (int i = 0; i < len; ++i) {
            int v = s[i] - 'a';
            if (!ch[u][v])
                return;
            u = ch[u][v];
        }
        // 单词不存在
        if (!isWord[u])
            return;
        u = 0;
        int pre, v;
        // 更新沿途节点作为前缀出现的次数
        for (int i = 0; i < len; ++i) {
            pre = u;
            v = s[i] - 'a';
            u = ch[u][v];
            --count[u];
        }
        // 删除单词
        isWord[u] = false;
        if (count[u] == 1)
            ch[pre][v] = 0;
    }

    // 0-不存在，1-存在，-1-被点过名
    int find(char* s) {
        int u = 0, len = strlen(s);
        for (int i = 0; i < len; ++i) {
            int v = s[i] - 'a';
            if (!ch[u][v])
                return 0;
            u = ch[u][v];
        }
        if (!isWord[u])
            return 0;
        if (ask[u])
            return -1;
        ask[u] = true;
        return 1;
    }
} trie;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int n, m;
    scanf("%d", &n);
    char name[55];
    while (n--) {
        scanf("%s", name);
        trie.insert(name);
    }
    scanf("%d", &m);
    while (m--) {
        scanf("%s", name);
        int ans = trie.find(name);
        if (ans == 0)
            printf("WRONG\n");
        else if (ans == -1)
            printf("REPEAT\n");
        else
            printf("OK\n");
    }
    return 0;
}