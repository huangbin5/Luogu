#include <cmath>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
const int INF = 0x7fffffff;

struct Node {
    Node* ch[2];
    int prior, data, dup, size;
    Node() {}
    Node(int _data, int _prior) : data(_data), prior(_prior), dup(1), size(1) {}
    int cmp(int x) const {
        if (x == data)
            return -1;
        return x > data;
    }
} * root;

void update(Node* v) {
    v->size = v->dup;
    if (v->ch[0])
        v->size += v->ch[0]->size;
    if (v->ch[1])
        v->size += v->ch[1]->size;
}

// 旋转：d = 0-左旋，1-右旋
void rotate(Node*& v, int d) {
    Node* p = v->ch[d ^ 1];
    v->ch[d ^ 1] = p->ch[d];
    p->ch[d] = v;
    // 先更新子树v的规模，再更新p的规模
    update(v);
    update(p);
    v = p;
}

// 插入：先按data插入到BST中，再根据prior旋转进行上滤
void insert(Node*& v, int data, int prior) {
    if (v == NULL) {
        v = new Node(data, prior);
        v->ch[0] = v->ch[1] = NULL;
        return;
    }
    int d = v->cmp(data);
    // 要插入的节点已存在
    if (d == -1) {
        ++v->dup;
        ++v->size;
        return;
    }
    // 递归插入到左右子树
    insert(v->ch[d], data, prior);
    update(v);
    // 插入完后进行旋转上虑调整
    if (v->ch[d]->prior > v->prior)
        rotate(v, d ^ 1);
}

// 删除：如果某棵子树为空，则用另一棵子树代替；否则先将优先级高的子树旋转上去，再递归删除另一棵子树
void remove(Node*& v, int data) {
    if (v == NULL)
        return;
    int d = v->cmp(data);
    if (d == -1) {
        if (v->dup > 1) {
            --v->dup;
            --v->size;
        } else {
            if (v->ch[0] == NULL)
                v = v->ch[1];
            else if (v->ch[1] == NULL)
                v = v->ch[0];
            else {
                int d2 = v->ch[0]->prior > v->ch[1]->prior;
                // 将优先级大的子树旋转至根后递归删除另一棵子树
                rotate(v, d2);
                remove(v->ch[d2], data);
                update(v);
            }
        }
    } else {
        remove(v->ch[d], data);
        update(v);
    }
}

// 查询排名为x的数
int ranc(Node* v, int x) {
    if (!v)
        return -1;
    int lcnt = v->ch[0] ? v->ch[0]->size : 0;
    if (lcnt < x && x <= lcnt + v->dup)
        return v->data;
    if (x <= lcnt)
        return ranc(v->ch[0], x);
    return ranc(v->ch[1], x - lcnt - v->dup);
}

// 查询x的排名
int find(Node* v, int x) {
    if (!v)
        return 1;
    int ans = v->ch[0] ? v->ch[0]->size : 0;
    if (x == v->data)
        return ans + 1;
    if (x < v->data)
        return find(v->ch[0], x);
    return ans + v->dup + find(v->ch[1], x);
}

// 找比x小的最大数
int prec(Node* v, int x) {
    if (!v)
        return -INF;
    if (v->data >= x)
        return prec(v->ch[0], x);
    return max(v->data, prec(v->ch[1], x));
}

// 找比x大的最小数
int succ(Node* v, int x) {
    if (!v)
        return INF;
    if (v->data <= x)
        return succ(v->ch[1], x);
    return min(v->data, succ(v->ch[0], x));
}
// --------------------------------------------------------------------------
struct PN {
    int lev;
    Node *p, *v;
    PN() {}
    PN(int _lev, Node* _p, Node* _v) : lev(_lev), p(_p), v(_v) {}
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
            q.push(PN(pn.lev + 1, pn.v, pn.v->ch[0]));
            q.push(PN(pn.lev + 1, pn.v, pn.v->ch[1]));
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
            insert(root, x, rand());
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
            printf("%d\n", prec(root, x));
            break;
        case 6:
            printf("%d\n", succ(root, x));
            break;
        }
    }
    return 0;
}