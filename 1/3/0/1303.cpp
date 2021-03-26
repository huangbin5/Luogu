#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

// d[0]存放最低位，高位往后面加
struct bigint {
    int len, data[10100];
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
    void init() {
        memset(data, 0, sizeof(data));
        len = 0;
    }
};

// 打印bigint
ostream& operator<<(ostream& cout, const bigint& a) {
    for (int i = a.len - 1; i >= 0; --i)
        cout << a.data[i];
    return cout;
}

bigint mul_high(const bigint& a, const bigint& b) {
    bigint c;
    // 两数相乘结果的长度只能为两数长度之和或减一
    c.len = a.len + b.len;
    for (int i = 0; i < a.len; ++i) {
        for (int j = 0; j < b.len; ++j) {
            // a[i] * b[j]的结果放在c[i+j]上，进位放在c[i+j+1]上
            int tmp = a.data[i] * b.data[j] + c.data[i + j];
            c.data[i + j] = tmp % 10;
            c.data[i + j + 1] += tmp / 10;
        }
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c.data[c.len - 1] == 0)
        --c.len;
    return c;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    string s;
    cin >> s;
    bigint a(s.c_str());
    cin >> s;
    bigint b(s.c_str());
    cout << mul_high(a, b);
    return 0;
}