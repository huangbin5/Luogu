#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5, MOD = 1e8 - 3;
int n, a[maxn], c[maxn], ans = 0;

struct Node {
    int v, r;
} a1[maxn], a2[maxn];

bool cmp(Node& n1, Node& n2) { return n1.v < n2.v; }

inline int lowbit(int x) { return x & (-x); }

// a[x] += v
void add(int x) {
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += 1;
}

int sum(int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a1[i].v;
        a1[i].r = i;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a2[i].v;
        a2[i].r = i;
    }
    sort(a1 + 1, a1 + n + 1, cmp);
    sort(a2 + 1, a2 + n + 1, cmp);
    for (int i = 1; i <= n; ++i)
        a[a1[i].r] = a2[i].r;
    for (int i = n; i > 0; --i) {
        add(a[i]);
        ans = (ans + sum(a[i] - 1)) % MOD;
    }
    cout << ans;
    return 0;
}