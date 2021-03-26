#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
typedef long long ll;

#define HB pair<Treap*, Treap*>
#define siz(v) ((v) ? ((v)->size) : 0)
struct Treap {
    int prior, data, size, tag;
    Treap *lc, *rc;
    Treap() {}
    Treap(int _data) : data(_data), prior(rand()), size(1), tag(0), lc(NULL), rc(NULL) {}
    inline void update() { size = 1 + siz(lc) + siz(rc); }
}* root = NULL;

// 下推是否交换的标记
void push_down(Treap* v) {
    if (v->tag) {
        // 需要实际交换左右子树
        swap(v->lc, v->rc);
        if (v->lc)
            v->lc->tag ^= 1;
        if (v->rc)
            v->rc->tag ^= 1;
        v->tag ^= 1;
    }
}

// 将以v为根的树中前k个元素分裂出来，得到两棵树
HB split(Treap* v, int k) {
    if (!v)
        return HB(NULL, NULL);
    // 下推标记
    push_down(v);
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
        // 下推标记
        push_down(u);
        u->rc = merge(u->rc, v);
        u->update();
        return u;
    } else {
        // 下推标记
        push_down(v);
        v->lc = merge(u, v->lc);
        v->update();
        return v;
    }
}

// 翻转区间
void reverse(int u, int v) {
    HB y = split(root, v);
    HB x = split(y.first, u - 1);
    x.second->tag ^= 1;
    root = merge(merge(x.first, x.second), y.second);
}

// 打印序列
void print(Treap* v) {
    if (!v)
        return;
    push_down(v);
    print(v->lc);
    printf("%d ", v->data);
    print(v->rc);
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    srand((unsigned int)time(NULL));
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i) {
        Treap* v = new Treap(i);
        root = merge(root, v);
    }
    int u, v;
    while (m--) {
        scanf("%d%d", &u, &v);
        reverse(u, v);
    }
    print(root);
    return 0;
}