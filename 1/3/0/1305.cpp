#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Node {
    char c;
    Node *lc, *rc;
    Node() { lc = rc = NULL; }
};
Node node[30];
// 出现过则+1，为孩子则-1
int root[30] = { 0 }, n;

void preOrder(Node* r) {
    if (r == NULL)
        return;
    cout << r->c;
    preOrder(r->lc);
    preOrder(r->rc);
}

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    char g, l, r;
    for (int i = 0; i < n; ++i) {
        cin.ignore();
        cin >> g >> l >> r;
        root[g - 'a']++;
        node[g - 'a'].c = g;
        if (l != '*') {
            root[l - 'a']--;
            node[g - 'a'].lc = &node[l - 'a'];
        }
        if (r != '*') {
            root[r - 'a']--;
            node[g - 'a'].rc = &node[r - 'a'];
        }
    }
    for (int i = 0; i < 30; ++i)
        if (root[i])
            preOrder(&node[i]);
    return 0;
}