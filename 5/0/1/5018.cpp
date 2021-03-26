#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Node {
    int id, weight, size;
    Node *lc, *rc;
    Node() { lc = rc = NULL; }
};

const int maxn = 1e6 + 5;
int n;
Node node[maxn];

int getSize(Node* r) {
    if (r == NULL)
        return 0;
    r->size = getSize(r->lc) + getSize(r->rc) + 1;
    return r->size;
}

bool check(Node* l, Node* r) {
    if (l == r)
        return true;
    if ((l == NULL) ^ (r == NULL))
        return false;
    if (l->weight != r->weight)
        return false;
    return check(l->lc, r->rc) && check(l->rc, r->lc);
}

inline int read() {
    int x = 0, sign = 1;
    char c = getchar();
    for (; c > '9' || c < '0'; c = getchar())
        if (c == '-')
            sign = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    return x * sign;
}

int main() {
#define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    // std::ios::sync_with_stdio(false);
    // cin >> n;
    // scanf("%d", &n);
    n = read();
    for (int i = 1; i <= n; ++i)
        // cin >> node[i].weight;
        // scanf("%d", &node[i].weight);
        node[i].weight = read();
    int lc, rc;
    for (int i = 1; i <= n; ++i) {
        node[i].id = i;
        // cin >> lc >> rc;
        // scanf("%d%d", &lc, &rc);
        lc = read(), rc = read();
        if (lc != -1)
            node[i].lc = &node[lc];
        if (rc != -1)
            node[i].rc = &node[rc];
    }
    getSize(&node[1]);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (check(node[i].lc, node[i].rc))
            ans = max(ans, node[i].size);
    cout << ans;
    return 0;
}