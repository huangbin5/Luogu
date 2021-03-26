#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int MOD = 1e9 + 7;

typedef struct matrix {
    ll** data;
    int r, c;
    // 空矩阵
    matrix(int _r, int _c)
        : r(_r)
        , c(_c) {
        init();
    }
    // 单位矩阵
    matrix(int n)
        : r(n)
        , c(n) {
        init();
        for (int i = 0; i < n; ++i)
            data[i][i] = 1;
    }
    // 拷贝构造函数
    matrix(matrix& a) {
        r = a.r, c = a.c;
        init();
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                data[i][j] = a[i][j];
    }
    void init() {
        // 在堆中开辟二维数组
        data = new ll*[r];
        data[0] = new ll[r * c];
        for (int i = 1; i < r; ++i)
            data[i] = data[i - 1] + c;
        memset(data[0], 0, sizeof(ll) * r * c);
    }
    ll*& operator[](int i) const { return data[i]; }
} matrix, E;

matrix operator*(const matrix& a, const matrix& b) {
    matrix c(a.r, b.c);
    for (int i = 0; i < c.r; ++i)
        for (int j = 0; j < c.c; ++j)
            for (int k = 0; k < a.c; ++k)
                c[i][j] = (c[i][j] + (a[i][k] * b[k][j]) % MOD) % MOD;
    return c;
}

matrix quickPow(matrix a, int b) {
    E c(a.r);
    while (b) {
        if (b & 1)
            c = c * a;
        a = a * a;
        b >>= 1;
    }
    return c;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int t, n;
    cin >> t;
    // 初始矩阵、变换矩阵
    matrix a3(1, 3), base(3, 3);
    a3[0][0] = a3[0][1] = a3[0][2] = 1;
    base[0][0] = base[0][1] = base[1][2] = base[2][0] = 1;
    for (int i = 0; i < t; ++i) {
        cin >> n;
        if (n <= 3)
            cout << 1 << endl;
        else
            cout << (a3 * quickPow(base, n - 3))[0][0] << endl;
    }
    return 0;
}