#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

struct Node {
    char type;
    Node *lc, *rc;
    Node() { lc = rc = NULL; }
    Node(char _type, Node* _lc = NULL, Node* _rc = NULL)
        : type(_type)
        , lc(_lc)
        , rc(_rc) {}
};

int n;
string s;
Node* root;

Node* build(int left, int right) {
    Node* r = new Node;
    string ss = s.substr(left, right - left);
    if (ss.find("0") == string::npos)
        r->type = 'I';
    else if (ss.find("1") == string::npos)
        r->type = 'B';
    else
        r->type = 'F';
    if (right - left > 1) {
        r->lc = build(left, (left + right) >> 1);
        r->rc = build((left + right) >> 1, right);
    }
    return r;
}

void postOrder(Node* r) {
    if (r == NULL)
        return;
    postOrder(r->lc);
    postOrder(r->rc);
    cout << r->type;
}

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> s;
    root = build(0, 1 << n);
    postOrder(root);
    return 0;
}