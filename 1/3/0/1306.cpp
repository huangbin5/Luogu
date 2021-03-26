#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int MOD = 1e8;

int gcd(int a, int b) {
    if (a < b)
        return gcd(b, a);
    if (a % b == 0)
        return b;
    return gcd(b, a % b);
}

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
matrix operator^(matrix a, int b) {
    E c(a.r);
    while (b) {
        if (b & 1)
            c = c * a;
        a = a * a;
        b >>= 1;
    }
    return c;
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    int g = gcd(n, m);
    if (g <= 2) {
        cout << 1;
        return 0;
    }
    matrix a2(1, 2), base(2, 2);
    a2[0][0] = a2[0][1] = 1;
    base[0][0] = base[0][1] = base[1][0] = 1;
    cout << (a2 * (base ^ (g - 2)))[0][0];
    return 0;
}