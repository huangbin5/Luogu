#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int MOD = 1e9 + 7, maxm = 5;
ll n, m, k;
bool legal[1 << maxm] = { false };

typedef struct matrix {
    ll** data;
    int r, c;
    // 空矩阵
    matrix(int _r, int _c) : r(_r), c(_c) { init(); }
    // 单位矩阵
    matrix(int n) : r(n), c(n) {
        init();
        for (int i = 0; i < n; ++i)
            data[i][i] = 1;
    }
    // 拷贝构造函数
    matrix(const matrix& a) { *this = a; }
    void init() {
        // 在堆中开辟二维数组
        data = new ll*[r];
        data[0] = new ll[r * c];
        for (int i = 1; i < r; ++i)
            data[i] = data[i - 1] + c;
        memset(data[0], 0, sizeof(ll) * r * c);
    }
    ll*& operator[](int i) const { return data[i]; }
    matrix& operator=(const matrix& a) {
        r = a.r, c = a.c;
        init();
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                data[i][j] = a[i][j];
        return *this;
    }
} matrix, E;

matrix operator*(const matrix& a, const matrix& b) {
    matrix c(a.r, b.c);
    for (int i = 0; i < c.r; ++i)
        for (int j = 0; j < c.c; ++j)
            for (int k = 0; k < a.c; ++k)
                c[i][j] = (c[i][j] + (a[i][k] * b[k][j]) % MOD) % MOD;
    return c;
}

// 不能传引用，否则会改变a的值，多次调用就会出错
matrix operator^(matrix a, ll b) {
    E c(a.r);
    while (b) {
        if (b & 1)
            c = c * a;
        a = a * a;
        b >>= 1;
    }
    return c;
}

void get_legal_status() {
    for (int i = 0; i < (1 << m); ++i) {
        int cnt = 0;
        for (int j = 0; j < m; ++j)
            if (i & (1 << j))
                ++cnt;
        if (cnt <= k)
            legal[i] = true;
    }
}

matrix get_base() {
    matrix ans(1 << m, 1 << m);
    for (int i = 0; i < (1 << m); ++i)
        if (legal[i])
            ans[i >> 1][i] = ans[(i >> 1) + (1 << (m - 1))][i] = 1;
    return ans;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m >> k;
    get_legal_status();
    // matrix base = get_base();
    // matrix a1(1, 1 << m);
    matrix an = get_base() ^ n;
    int ans = 0;
    for (int i = 0; i < (1 << m); ++i)
        // if (legal[i]) {
        //     a1[0][i] = 1;
        //     ans = (ans + (a1 * (base ^ n))[0][i]) % MOD;
        //     a1[0][i] = 0;
        // }
        ans = (ans + an[i][i]) % MOD;
    cout << ans;
    return 0;
}