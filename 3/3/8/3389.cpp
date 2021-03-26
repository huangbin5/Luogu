#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
typedef double ll;
const double eps = 1e-8;

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

bool gauss(matrix& a) {
    int n = a.r;
    // 对第i行消元
    for (int i = 0; i < n; ++i) {
        // 选择i ~ n-1行中首列元素绝对值最大的行
        int r = i;
        for (int k = i + 1; k < n; ++k)
            if (fabs(a[k][i]) > fabs(a[r][i]))
                r = k;
        // 将该行移到第i行
        if (r != i)
            for (int j = 0; j <= n; ++j)
                swap(a[i][j], a[r][j]);
        // 与第i+1 ~ n-1行消元
        for (int k = i + 1; k < n; ++k)
            // 这里必须逆序进行，保证a[k][i]最后一个被消除
            for (int j = n; j >= i; --j)
                a[k][j] -= a[i][j] * a[k][i] / a[i][i];
    }
    // 消元后进行回代
    for (int i = n - 1; i >= 0; --i) {
        if (fabs(a[i][i]) < eps)
            return false;
        for (int j = n - 1; j > i; --j)
            a[i][n] -= a[i][j] * a[j][n];
        a[i][n] /= a[i][i];
    }
    return true;
}

bool gauss_jordan(matrix& a) {
    int n = a.r;
    for (int i = 0; i < n; ++i) {
        int r = i;
        for (int k = i + 1; k < n; ++k)
            if (fabs(a[k][i]) > fabs(a[r][i]))
                r = k;
        if (fabs(a[r][i]) < eps)
            return false;
        if (r != i)
            for (int j = 0; j <= n; ++j)
                swap(a[i][j], a[r][j]);
        // 与除了第i行的其它行消元，无需回代过程
        for (int k = 0; k < n; ++k)
            if (k != i)
                for (int j = n; j >= i; --j)
                    a[k][j] -= a[i][j] * a[k][i] / a[i][i];
    }
    return true;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int n;
    cin >> n;
    matrix a(n, n + 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j <= n; ++j)
            cin >> a[i][j];
    if (gauss_jordan(a))
        for (int i = 0; i < n; ++i)
            cout << fixed << setprecision(2) << a[i][n] / a[i][i] << endl;
    else
        cout << "No Solution";
    return 0;
}