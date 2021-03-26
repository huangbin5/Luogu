#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 3e5 + 50;
typedef long long LL;
typedef pair<LL, LL> P; //用于存储好的配对的结构体
struct node1 { //用于将输入数组排序的结构体
    LL x; //值
    LL id; //存对应的原数组的编号，为了统计好的配对
};
struct node2 { //用于将区间排序的结构体
    LL l; //左端点
    LL r; //右端点
    LL id; //存对应的原区间的编号，为了计算答案
};
node1 a[MAXN << 1]; //存储输入数组
node2 b[MAXN << 1]; //存储输入区间
P mix[MAXN << 1]; //存储好的配对
LL N, M, l, r, sub[MAXN << 1], c[MAXN << 1], ans[MAXN << 1], h = 0, Ans = 0; // c为树状数组，ans为答案数组
bool cmp1(node1 a, node1 b) { return a.x < b.x; } //用于给输入数组排序
bool cmp2(P a, P b) { return a.first < b.first; } //用于给好的配对排序
bool cmp3(node2 a, node2 b) { return a.l != b.l ? a.l < b.l : a.r < b.r; } //用于给区间排序
inline void add(node1 a, node1 b) { //统计好的配对的函数
    mix[++h].first = min(a.id, b.id);
    mix[h].second = max(a.id, b.id);
}
inline LL lowbit(LL x) { return x & -x; }
inline void change(LL c[], LL len, LL now, LL k) { //单点修改
    while (now <= len) {
        c[now] += k;
        now += lowbit(now);
    }
}
inline LL query(LL c[], LL len, LL now) { //区间查询
    LL res = 0;
    while (now) {
        res += c[now];
        now -= lowbit(now);
    }
    return res;
}
#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    memset(c, 0, sizeof(c));
    scanf("%lld%lld", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%lld", &a[i].x), a[i].id = i;
    sort(a + 1, a + 1 + N, cmp1); //先将输入数组排序
    add(a[2], a[1]);
    add(a[N], a[N - 1]); //对于第一个和最后一个数据特殊处理
    for (int i = 2; i < N; i++) { //对于其他数据，统计好的配对的数量并且保存对应的x,y
        if (abs(a[i].x - a[i - 1].x) == abs(a[i + 1].x - a[i].x)) { //以下是好的配对的三种情况
            add(a[i], a[i - 1]);
            add(a[i + 1], a[i]);
        }
        if (abs(a[i].x - a[i - 1].x) < abs(a[i + 1].x - a[i].x))
            add(a[i], a[i - 1]);
        if (abs(a[i].x - a[i - 1].x) > abs(a[i + 1].x - a[i].x))
            add(a[i + 1], a[i]);
    }
    sort(mix + 1, mix + 1 + h, cmp2); //将好的配对排序
    for (int i = 1; i <= M; i++)
        scanf("%lld%lld", &b[i].l, &b[i].r), b[i].id = i;
    sort(b + 1, b + 1 + M, cmp3); //将区间排序
    int now = h; //指针
    for (int i = M; i >= 1; i--) {
        while (mix[now].first >= b[i].l) { //将所有有贡献的好的配对加入
            change(c, N, mix[now].second, 1);
            now--; //指针左移
        }
        ans[b[i].id] = query(c, N, b[i].r); //统计区间(l[i],r[i])内的好的配对的数量并保存进ans数组
    }
    for (int i = 1; i <= M; i++)
        Ans += ans[i] * i; //计算答案
    printf("%lld\n", Ans);
    return 0;
}