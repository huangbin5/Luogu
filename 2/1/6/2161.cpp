#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 5;
int n, c[maxn] = { 0 }, et[maxn] = { 0 };

inline int lowbit(int x) { return x & (-x); }

// a[x] += v
void add(int x, int v) {
    for (int i = x; i <= maxn; i += lowbit(i))
        c[i] += v;
}

int sum(int x) {
    int ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}

// sum(x, y)
int sum(int x, int y) { return sum(y) - sum(x - 1); }

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    scanf("%d", &n);
    char op[5];
    int u, v;
    while (n--) {
        scanf("%s%d%d", op, &u, &v);
        if (op[0] == 'A') {
            int sum_v, ans = 0;
            while (sum_v = sum(v)) {
                int l = 0, r = v;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (sum(mid) < sum_v)
                        l = mid + 1;
                    else
                        r = mid - 1;
                }
                if (et[l] >= u) {
                    add(l, -1);
                    ++ans;
                } else
                    break;
            }
            add(u, 1);
            et[u] = v;
            printf("%d\n", ans);
        } else
            printf("%d\n", sum(maxn));
    }
    return 0;
}