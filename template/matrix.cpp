#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105;
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

ostream& operator<<(ostream& cout, const matrix& a);
matrix operator+(const matrix& a, const matrix& b);
matrix operator*(const matrix& a, const matrix& b);

ostream& operator<<(ostream& cout, const matrix& a) {
    for (int i = 0; i < a.r; ++i)
        for (int j = 0; j < a.c; ++j) {
            cout << a[i][j];
            if (j != a.c - 1)
                cout << " ";
            else if (i != a.r - 1)
                cout << endl;
        }
    return cout;
}

matrix operator+(const matrix& a, const matrix& b) {
    matrix c(a.r, a.c);
    for (int i = 0; i < c.r; ++i)
        for (int j = 0; j < c.c; ++j)
            c[i][j] = a[i][j] + b[i][j];
    return c;
}

matrix operator*(const matrix& a, const matrix& b) {
    matrix c(a.r, b.c);
    for (int i = 0; i < c.r; ++i)
        for (int j = 0; j < c.c; ++j)
            for (int k = 0; k < a.c; ++k)
                c[i][j] += a[i][k] * b[k][j];
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
    matrix a(3, 3), b(3, 3);
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            a[i][j] = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            b[i][j] = 2;
    cout << a << endl << b << endl << endl;
    matrix c(a);
    // c = a;
    cout << a << endl << c << endl << endl;
    c[1][1] = 9;
    cout << a << endl << c << endl << endl;
    return 0;
}