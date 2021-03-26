#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

struct Node {
    char c;
    Node *lc, *rc;
    Node() { lc = rc = NULL; }
    Node(char _c, Node* _lc = NULL, Node* _rc = NULL)
        : c(_c)
        , lc(_lc)
        , rc(_rc) {}
};

string inOrder, postOrder;
Node* root;

Node* build(int inL, int inR, int postL, int postR) {
    if (inL > inR)
        return NULL;
    Node* r = new Node(postOrder[postR]);
    int mid;
    for (mid = inL; mid <= inR; ++mid)
        if (inOrder[mid] == postOrder[postR])
            break;
    r->lc = build(inL, mid - 1, postL, postL + mid - inL - 1);
    r->rc = build(mid + 1, inR, postR - inR + mid, postR - 1);
    return r;
}

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
    cin >> inOrder >> postOrder;
    root = build(0, inOrder.size() - 1, 0, postOrder.size() - 1);
    preOrder(root);
    return 0;
}