#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
const int INF = 0x7fffffff;

#define HB pair<Treap*, Treap*>
#define siz(v) ((v) ? ((v)->size) : 0)
struct Treap {
    int prior, data, size;
    Treap *lc, *rc;
    Treap() {}
    Treap(int _data) : data(_data), prior(rand()), size(1), lc(NULL), rc(NULL) {}
    inline void update() { size = 1 + siz(lc) + siz(rc); }
}* root = NULL;

// 将以v为根的树中前k个元素分裂出来，得到两棵树
HB split(Treap* v, int k) {
    if (!v)
        return HB(NULL, NULL);
    HB hb;
    if (k <= siz(v->lc)) {
        hb = split(v->lc, k);
        v->lc = hb.second;
        v->update();
        hb.second = v;
    } else {
        hb = split(v->rc, k - siz(v->lc) - 1);
        v->rc = hb.first;
        v->update();
        hb.first = v;
    }
    return hb;
}

// 将以u为根和以v为根的树合并(默认u中的元素都小于v)
Treap* merge(Treap* u, Treap* v) {
    if (!u)
        return v;
    if (!v)
        return u;
    if (u->prior > v->prior) {
        u->rc = merge(u->rc, v);
        u->update();
        return u;
    } else {
        v->lc = merge(u, v->lc);
        v->update();
        return v;
    }
}

// 查询排名为k的数(注意传引用)
int ranc(Treap*& v, int k) {
    if (!v)
        return 0;
    HB x = split(v, k - 1);
    HB y = split(x.second, 1);
    v = merge(x.first, merge(y.first, y.second));
    return y.first->data;
}

// 查询key的排名
int find(Treap* v, int key) {
    if (!v)
        return 1;
    if (key <= v->data)
        return find(v->lc, key);
    return siz(v->lc) + 1 + find(v->rc, key);
}

// 插入key(注意传引用)
void insert(Treap*& v, int key) {
    HB hb = split(v, find(v, key) - 1);
    v = merge(hb.first, merge(new Treap(key), hb.second));
}

// 删除key(注意传引用)
void remove(Treap*& v, int key) {
    HB x = split(v, find(v, key) - 1);
    HB y = split(x.second, 1);
    if (y.first->data != key)
        v = merge(x.first, merge(y.first, y.second));
    else
        v = merge(x.first, y.second);
}

// 查询比key小的最大数
int prec(int key) { return ranc(root, find(root, key) - 1); }

// 查询比key大的最小数
int succ(int key) { return ranc(root, find(root, key + 1)); }

// --------------------------------------------------------------------------
struct PN {
    int lev;
    Treap *p, *v;
    PN() {}
    PN(int _lev, Treap* _p, Treap* _v) : lev(_lev), p(_p), v(_v) {}
};
void print(int i) {
    puts("");
    printf("line %d:\n", i);
    queue<PN> q;
    q.push(PN(1, NULL, root));
    int pre = 0;
    while (!q.empty()) {
        PN pn = q.front();
        q.pop();
        if (pn.v) {
            pre == pn.lev ? printf("\t%d\t%d\t%d\n", pn.p ? pn.p->data : -1, pn.v->data, pn.v->size)
                          : printf("%d:\t%d\t%d\t%d\n", pre = pn.lev, pn.p ? pn.p->data : -1, pn.v->data, pn.v->size);
            q.push(PN(pn.lev + 1, pn.v, pn.v->lc));
            q.push(PN(pn.lev + 1, pn.v, pn.v->rc));
        }
    }
    fflush(stdout);
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    srand((unsigned int)time(NULL));
    int n, t, x;
    scanf("%d", &n);
    for (int i = 2; i <= n + 1; ++i) {
        scanf("%d%d", &t, &x);
        // print(i);
        switch (t) {
        case 1:
            insert(root, x);
            break;
        case 2:
            remove(root, x);
            break;
        case 3:
            printf("%d\n", find(root, x));
            break;
        case 4:
            printf("%d\n", ranc(root, x));
            break;
        case 5:
            printf("%d\n", prec(x));
            break;
        case 6:
            printf("%d\n", succ(x));
            break;
        }
    }
    return 0;
}