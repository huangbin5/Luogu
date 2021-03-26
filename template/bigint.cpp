#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;
typedef complex<double> cd;
const double PI = acos(-1.0);
const int maxn = 10005;

// d[0]存放最低位，高位往后面加
struct bigint {
    int len, *data;
    bigint() { init(); }
    // 整数
    bigint(ll a) {
        init();
        // 特殊情况0
        if (a == 0)
            len = 1;
        while (a > 0) {
            data[len++] = a % 10;
            a /= 10;
        }
    }
    // 字符数组
    bigint(const char* s) {
        init();
        len = strlen(s);
        for (int i = 0; i < len; ++i)
            data[len - 1 - i] = s[i] - '0';
    }
    // 拷贝构造函数
    bigint(const bigint& a) { *this = a; }
    void init() {
        data = new int[maxn];
        memset(data, 0, sizeof(int) * maxn);
        len = 0;
    }
    // 访问元素
    int& operator[](int i) const { return data[i]; }
    bigint& operator=(const bigint& a) {
        init();
        len = a.len;
        for (int i = 0; i < len; ++i)
            data[i] = a[i];
        return *this;
    }
};

// 打印
ostream& operator<<(ostream& cout, const bigint& a);
// 比较
int compare(const bigint& a, const bigint& b);
// 乘以或除以10
bigint operator<<(const bigint& a, int n);
bigint operator>>(const bigint& a, int n);
bigint& operator<<=(bigint& a, int n);
bigint& operator>>=(bigint& a, int n);

// 加
bigint add(const bigint& a, const bigint& b);
// 减
bigint sub(const bigint& a, const bigint& b);
// 乘
bigint mul_low(const bigint& a, int b);
bigint mul_high(const bigint& a, const bigint& b);
void fft(vector<cd>& v, bool inverse);
bigint mul_fft(const bigint& a, const bigint& b);
// 除
bigint div_low(const bigint& a, int b, int& r);
bigint div_high(const bigint& a, const bigint& b, bigint& r);

// 阶乘
bigint fac(int n);
// 幂
bigint pow(const bigint& a, int b);
// 平方根
bigint sqrt(const bigint& a);

// 打印bigint
ostream& operator<<(ostream& cout, const bigint& a) {
    for (int i = a.len - 1; i >= 0; --i)
        cout << a[i];
    return cout;
}

// 比较两个bigint的大小
int compare(const bigint& a, const bigint& b) {
    if (a.len > b.len)
        return 1;
    else if (a.len < b.len)
        return -1;
    for (int i = a.len - 1; i >= 0; --i)
        if (a[i] > b[i])
            return 1;
        else if (a[i] < b[i])
            return -1;
    return 0;
}

// 将bigint左移n位
bigint operator<<(const bigint& a, int n) {
    bigint c;
    for (int i = a.len - 1; i >= 0; --i)
        c[i + n] = a[i];
    for (int i = 0; i < n; ++i)
        c[i] = 0;
    c.len = a.len + n;
    return c;
}

// 将bigint右移n位
bigint operator>>(const bigint& a, int n) {
    bigint c;
    c.len = a.len - n;
    for (int i = 0; i < c.len; ++i)
        c[i] = a[i + n];
    for (int i = c.len; i < a.len; ++i)
        c[i] = 0;
    return c;
}

// 将bigint左移n位
bigint& operator<<=(bigint& a, int n) {
    for (int i = a.len - 1; i >= 0; --i)
        a[i + n] = a[i];
    for (int i = 0; i < n; ++i)
        a[i] = 0;
    a.len += n;
    return a;
}

// 将bigint右移n位
bigint& operator>>=(bigint& a, int n) {
    a.len -= n;
    for (int i = 0; i < a.len; ++i)
        a[i] = a[i + n];
    for (int i = a.len; i < a.len + n; ++i)
        a[i] = 0;
    return a;
}

// bigint + bigint
bigint add(const bigint& a, const bigint& b) {
    bigint c;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        int tmp = a[i] + b[i] + carry;
        c[c.len++] = tmp % 10;
        carry = tmp / 10;
    }
    // 最高位有进位
    if (carry)
        c[c.len++] = carry;
    return c;
}

// 大bigint - 小bigint
bigint sub(const bigint& a, const bigint& b) {
    bigint c;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        int tmp = a[i] - b[i] - carry + 10;
        c[c.len++] = tmp % 10;
        carry = (tmp / 10) ^ 1;
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c[c.len - 1] == 0)
        --c.len;
    return c;
}

// bigint * int
bigint mul_low(const bigint& a, int b) {
    bigint c;
    int carry = 0;
    for (int i = 0; i < a.len; ++i) {
        int tmp = a[i] * b + carry;
        c[c.len++] = tmp % 10;
        carry = tmp / 10;
    }
    // 可能有多位进位
    while (carry) {
        c[c.len++] = carry % 10;
        carry /= 10;
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c[c.len - 1] == 0)
        --c.len;
    return c;
}

// bigint * bigint
bigint mul_high(const bigint& a, const bigint& b) {
    bigint c;
    // 两数相乘结果的长度只能为两数长度之和或减一
    c.len = a.len + b.len;
    for (int i = 0; i < a.len; ++i) {
        for (int j = 0; j < b.len; ++j) {
            // a[i] * b[j]的结果放在c[i + j]上，进位放在c[i + j + 1]上
            int tmp = a[i] * b[j] + c[i + j];
            c[i + j] = tmp % 10;
            c[i + j + 1] += tmp / 10;
        }
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c[c.len - 1] == 0)
        --c.len;
    return c;
}

/**
 * 如果要记录每个数字的位反转结果，也可以按如下方法：
 * // 先将除最低位的高位数字反转到低位，再将最低位填充到反转后的最高位
 * anti[idx] = (anti[idx >> 1] >> 1) | ((idx & 1) ? (len >> 1) : 0);
 */
void fft(vector<cd>& v, bool inverse) {
    /**
     * 原地快速位反转(bit reversal)
     * len：多项式的长度
     * idx：遍历从0~len-1的每个数
     * anti：记录着idx的位反转
     */
    int len = v.size();
    // 初始时idx=anti=0 (0的位反转仍为0)
    for (int idx = 0, anti = 0; idx < len; idx++) {
        // 判断的目的是让互为位反转的两个数只交换一次
        if (anti > idx)
            swap(v[idx], v[anti]);
        int test = len;
        // 从最高位开始测试anti是否为0
        while (anti & (test >>= 1))
            // 如果是1，则将该位置为0
            anti &= ~test;
        // 将高位的所有1置为0后，再将最高位的0置为1
        anti |= test;
        // 位反转过来看的话相当于加了1，因此此时anti就顺利记录着下一个idx的位反转
    }
    // 如果是IFFT，应选用共轭复数
    double pi = inverse ? -PI : PI;
    // 自底向上迭代，将两个half长的合并成一个2*half长的
    for (int half = 1; half < len; half <<= 1) {
        // 单位根增量
        cd w1 = exp(cd(0, pi / half));
        // 遍历每一组
        for (int start = 0; start < len; start += (half << 1)) {
            // 从单位根w0开始
            cd w = 1;
            // 更新组内的每一个数
            for (int cur = start; cur < start + half; ++cur) {
                cd x = v[cur];
                cd y = w * v[cur + half];
                // FFT核心：蝴蝶变换
                v[cur] = x + y;
                v[cur + half] = x - y;
                // 求下一个单位根
                w *= w1;
            }
        }
    }
    // 如果是IFFT，得到的每个数还要除以len
    if (inverse)
        for (int i = 0; i < len; ++i)
            v[i] /= len;
}

// FFT加速bigint * bigint
bigint mul_fft(const bigint& a, const bigint& b) {
    bigint c;
    c.len = 2;
    // 把长度补成不小于a与b长度之和的2的次幂
    while (c.len < a.len + b.len)
        c.len <<= 1;
    // 将两个bigint转化为两个多项式
    vector<cd> v1(c.len, 0), v2(c.len, 0);
    for (int i = 0; i < a.len; ++i)
        v1[i] = a[i];
    for (int i = 0; i < b.len; ++i)
        v2[i] = b[i];
    // 将两个多项式经FFT转化为点值表示法
    fft(v1, false);
    fft(v2, false);
    // 相乘
    for (int i = 0; i < c.len; ++i)
        v1[i] *= v2[i];
    // 将结果经IFFT转化为多系数表示法
    fft(v1, true);
    // 将多项式转化为bigint，由于多项式系数可能为多位数，因此应按进位加到下一位
    for (int i = 0; i < c.len; ++i) {
        int tmp = c[i] + (int)(v1[i].real() + 0.5);
        c[i] = tmp % 10;
        c[i + 1] = tmp / 10;
    }
    // 删除前导0，如果为0需要保留一个0
    // 由于前面长度补成了2的次幂，因此可能有多个前导0
    while (c.len > 1 && c[c.len - 1] == 0)
        --c.len;
    return c;
}

// bigint / int, r为余数
bigint div_low(const bigint& a, int b, int& r) {
    bigint c;
    c.len = a.len;
    // 从高位开始
    for (int i = a.len - 1; i >= 0; --i) {
        int tmp = r * 10 + a[i];
        c[i] = tmp / b;
        r = tmp % b;
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c[c.len - 1] == 0)
        --c.len;
    return c;
}

// 大bigint / 小bigint
bigint div_high(const bigint& a, const bigint& b, bigint& r) {
    r = a;
    if (compare(a, b) < 0)
        return 0ll;
    // 将b与a位数对齐，末尾补0
    bigint tb = b << (a.len - b.len), c;
    c.len = a.len - b.len + 1;
    // 从高位开始计算c的每一位
    for (int i = c.len - 1; i >= 0; --i) {
        // 不断用ta减去tb，用减法模拟除法做商
        while (compare(r, tb) >= 0) {
            ++c[i];
            r = sub(r, tb);
        }
        tb >>= 1;
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c[c.len - 1] == 0)
        --c.len;
    return c;
}

// int阶乘，但结果为bigint
bigint fac(int n) {
    bigint ans = 1;
    for (int i = 2; i <= n; ++i)
        ans = mul_low(ans, i);
    return ans;
}

// FFT乘 + 二分求幂
bigint pow(const bigint& a, int b) {
    if (b == 0)
        return 1;
    if (b & 1)
        return mul_fft(pow(a, b - 1), a);
    bigint tmp = pow(a, b >> 1);
    return mul_fft(tmp, tmp);
}

// FFT乘 + 二分求平方根，取整数部分
bigint sqrt(const bigint& a) {
    bigint left = 1, right = a, mid;
    int r;
    while (compare(left, right) <= 0) {
        r = 0;
        mid = div_low(add(left, right), 2, r);
        if (compare(mul_fft(mid, mid), a) <= 0)
            left = add(mid, 1);
        else
            right = sub(mid, 1);
    }
    return right;
}

int main() {
#define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int bi = 10;
    bigint a("3456567568678567456756867858756785867985677656745747546757657474675467546563647567586787967856756758678678678567"),
        b("4632472354398556748957698576485674856739847564986749586039485209350198310983904583940534656867878");
    cout << a << " ++ " << b << " = " << add(a, b) << endl << endl;
    cout << a << " -- " << b << " = " << sub(a, b) << endl << endl;
    cout << a << " *l " << bi << " = " << mul_low(a, bi) << endl << endl;
    cout << a << " *h " << b << " = " << mul_high(a, b) << endl << endl;
    cout << a << " *f " << b << " = " << mul_fft(a, b) << endl << endl;
    int r1 = 0;
    cout << a << " /l " << bi << " = " << div_low(a, bi, r1) << "..." << r1 << endl << endl;
    bigint r2;
    cout << a << " /h " << b << " = " << div_high(a, b, r2) << "..." << r2 << endl << endl;
    cout << bi << " ! = " << fac(bi) << endl << endl;
    cout << a << " ^ " << bi << " = " << pow(a, bi) << endl << endl;
    cout << a << " @ = " << sqrt(a) << endl << endl;
    bigint c = mul_high(a, b);
    cout << c << endl << endl;
    bigint d(a);
    cout << d << endl << endl;
    d = b;
    cout << d << endl << endl;
    d[0] = 1;
    cout << d << endl << endl;
    cout << b << endl << endl;
    return 0;
}