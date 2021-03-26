#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 5;

struct SmallHeap {
    int size, data[maxn];
    SmallHeap() { size = 0; }

    int get() { return data[1]; }

    void insert(int a) {
        data[++size] = a;
        int v = size, u = size / 2;
        while (u > 0 && data[u] > data[v]) {
            swap(data[u], data[v]);
            v = u, u = v / 2;
        }
    }

    void del() {
        data[1] = data[size--];
        int u = 1, v = 1;
        for (;;) {
            if (2 * u <= size && data[2 * u] < data[v])
                v = 2 * u;
            if (2 * u + 1 <= size && data[2 * u + 1] < data[v])
                v = 2 * u + 1;
            if (u == v)
                break;
            swap(data[u], data[v]);
            u = v;
        }
    }

    void clear_print() {
        while (size > 0) {
            cout << get() << " ";
            del();
        }
        cout << endl;
    }
};

struct BigHeap {
    int size, data[maxn];
    BigHeap() { size = 0; }

    int get() { return data[1]; }

    void insert(int a) {
        data[++size] = a;
        int v = size, u = size / 2;
        while (u > 0 && data[u] < data[v]) {
            swap(data[u], data[v]);
            v = u, u = v / 2;
        }
    }

    void del() {
        data[1] = data[size--];
        int u = 1, v = 1;
        for (;;) {
            if (2 * u <= size && data[2 * u] > data[v])
                v = 2 * u;
            if (2 * u + 1 <= size && data[2 * u + 1] > data[v])
                v = 2 * u + 1;
            if (u == v)
                break;
            swap(data[u], data[v]);
            u = v;
        }
    }

    void clear_print() {
        while (size > 0) {
            cout << get() << " ";
            del();
        }
        cout << endl;
    }
};

int n, m, a[maxn], b[maxn];

inline int read() {
    int x = 0, sign = 1;
    char c = getchar();
    // 符号
    for (; c < '0' || '9' < c; c = getchar())
        if (c == '-')
            sign = -1;
    // 多位数字
    for (; '0' <= c && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    return x * sign;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    SmallHeap sh;
    BigHeap bh;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        a[i] = read();
    for (int i = 1; i <= m; ++i) {
        b[i] = read();
        if (i > 1) {
            bh.insert(sh.get());
            sh.del();
        }
        for (int j = b[i - 1] + 1; j <= b[i]; ++j)
            if (a[j] >= bh.get())
                sh.insert(a[j]);
            else {
                sh.insert(bh.get());
                bh.del();
                bh.insert(a[j]);
            }
        printf("%d\n", sh.get());
    }
    return 0;
}