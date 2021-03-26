#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 2e5 + 5;
int n, m;
char input[maxn];
int a[maxn];

// 注意要开4倍空间
struct Node {
    int l, r, sum, tag;
} seg[maxn << 2];

// 建树
void build(int p, int l, int r) {
    seg[p].l = l, seg[p].r = r;
    // 叶节点
    if (l == r) {
        seg[p].sum = a[l];
        return;
    }
    int lc = p << 1, rc = lc | 1, mid = (l + r) >> 1;
    // 递归建左右子树
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg[p].sum = seg[lc].sum + seg[rc].sum;
}

// 下推懒标记
void push_down(int p) {
    if (seg[p].tag) {
        int lc = p << 1, rc = lc | 1;
        // 更新子节点
        seg[lc].sum = seg[lc].r - seg[lc].l + 1 - seg[lc].sum;
        seg[rc].sum = seg[rc].r - seg[rc].l + 1 - seg[rc].sum;
        seg[lc].tag ^= 1;
        seg[rc].tag ^= 1;
        // 清除标记
        seg[p].tag = 0;
    }
}

// 区间修改
void modify(int p, int l, int r) {
    // 节点p在修改区间的内部
    if (l <= seg[p].l && seg[p].r <= r) {
        seg[p].sum = seg[p].r - seg[p].l + 1 - seg[p].sum;
        seg[p].tag ^= 1;
        return;
    }
    push_down(p);
    int lc = p << 1, rc = lc | 1;
    // 涉及到了左孩子
    if (l <= seg[lc].r)
        modify(lc, l, r);
    // 涉及到了右孩子
    if (r >= seg[rc].l)
        modify(rc, l, r);
    seg[p].sum = seg[lc].sum + seg[rc].sum;
}

// 区间查询
int sum(int p, int l, int r) {
    if (l <= seg[p].l && seg[p].r <= r)
        return seg[p].sum;
    push_down(p);
    int lc = p << 1, rc = lc | 1, ans = 0;
    if (l <= seg[lc].r)
        ans += sum(lc, l, r);
    if (r >= seg[rc].l)
        ans += sum(rc, l, r);
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d%d%s", &n, &m, input);
    for (int i = 1; i <= n; ++i)
        a[i] = input[i - 1] - '0';
    build(1, 1, n);
    int type, left, right;
    while (m--) {
        scanf("%d%d%d", &type, &left, &right);
        if (type == 0)
            modify(1, left, right);
        else
            cout << sum(1, left, right) << endl;
    }
    return 0;
}