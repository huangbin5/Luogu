#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Node {
    int data, dup, size;
    Node *lc, *rc, *parent;
    Node() {}
    Node(int _data, Node* _lc = NULL, Node* _rc = NULL, Node* _parent = NULL)
        : data(_data), dup(1), lc(_lc), rc(_rc), parent(_parent) {}
} * root;

// 更新子树的规模
void update(Node* v) {
    if (!v) {
        printf("update: v is NULL\n");
        return;
    }
    v->size = v->dup;
    if (v->lc)
        v->size += v->lc->size;
    if (v->rc)
        v->size += v->rc->size;
}

// 将v上移一层
void rotate(Node* v) {
    if (!(v && v->parent)) {
        printf("rotate: v or p is NULL\n");
        return;
    }
    // 是否顺时针旋转
    bool zig = (v == v->parent->lc ? true : false);
    Node *p = v->parent, *g = p->parent, *r = zig ? v->rc : v->lc;
    v->parent = g, g == NULL ? root = v : (p == g->lc ? g->lc = v : g->rc = v);
    p->parent = v, zig ? v->rc = p : v->lc = p;
    if (r)
        r->parent = p;
    zig ? p->lc = r : p->rc = r;
    // 更新树的规模
    update(p), update(v);
}

// 将v伸展至根
void splay(Node* v) {
    if (!v) {
        printf("splay: v is NULL\n");
        return;
    }
    Node *p, *g;
    while ((p = v->parent) && (g = p->parent))
        if ((v == p->lc) ^ (p == g->lc))
            rotate(v), rotate(v);
        else
            rotate(p), rotate(v);
    if (p = v->parent)
        rotate(v);
}

// 查询排名为x的数
int ranc(int x) {
    Node* v = root;
    while (v) {
        int r = v->lc ? v->lc->size : 0;
        if (r < x && x <= r + v->dup)
            break;
        x <= r ? v = v->lc : (x -= r + v->dup, v = v->rc);
    }
    if (!v) {
        printf("ranc: v is NULL\n");
        return NAN;
    }
    splay(v);
    // 默认存在，即v不为空
    return v->data;
}

// 查询x的排名(x不存在也有排名)
int find(int x) {
    if (!root)
        return 1;
    Node *v = root, *p;
    while (v) {
        p = v;
        if (x == v->data)
            break;
        v = (x < v->data ? v->lc : v->rc);
    }
    splay(p);
    int ans = (p->data >= x ? 1 : p->dup + 1);
    return p->lc ? ans + p->lc->size : ans;
}

// 找比x小的最大数
int prec(int x) {
    find(x);
    if (!root) {
        printf("prec: root is NULL\n");
        return NAN;
    }
    // 默认存在，即root->lc不为空
    if (root->data < x)
        return root->data;
    if (!root->lc) {
        printf("prec: not found\n");
        return NAN;
    }
    Node *v = root->lc, *p = root;
    while (v)
        p = v, v = v->rc;
    return p->data;
}

// 找比x大的最小数
int succ(int x) {
    find(x);
    if (!root) {
        printf("succ: root is NULL\n");
        return NAN;
    }
    // 默认存在，即root->rc不为空
    if (root->data > x)
        return root->data;
    if (!root->rc) {
        printf("succ: not found\n");
        return NAN;
    }
    Node *v = root->rc, *p = root;
    while (v)
        p = v, v = v->lc;
    return p->data;
}

// 插入x
void insert(int x) {
    if (!root) {
        root = new Node(x);
        update(root);
        return;
    }
    find(x);
    if (root->data == x) {
        ++root->dup;
        update(root);
        return;
    }
    bool big = x > root->data ? true : false;
    Node *p = root, *r = big ? p->rc : p->lc;
    p->parent = root = big ? new Node(x, p, r) : new Node(x, r, p);
    big ? p->rc = NULL : p->lc = NULL;
    if (r)
        r->parent = root;
    update(p), update(root);
}

// 删除x(若有多个只删除1个)
void del(int x) {
    if (!root)
        return;
    find(x);
    if (root->data != x)
        return;
    if (root->dup > 1) {
        --root->dup;
        update(root);
        return;
    }
    if (!root->lc) {
        root = root->rc;
        if (root)
            root->parent = NULL;
    } else if (!root->rc) {
        root = root->lc;
        root->parent = NULL;
    } else {
        Node* lc = root->lc;
        root = root->rc, root->parent = NULL;
        find(x);
        root->lc = lc, lc->parent = root;
        update(root);
    }
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cout << ranc(1);
    return 0;
}