#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

// d[0]存放最低位，高位往后面加
struct bigint {
    int len, data[505];
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

// bigint + bigint
bigint add(const bigint& a, const bigint& b) {
    bigint c;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        int tmp = a.data[i] + b.data[i] + carry;
        c.data[c.len++] = tmp % 10;
        carry = tmp / 10;
    }
    // 最高位有进位
    if (carry)
        c.data[c.len++] = carry;
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
    cout << add(a, b);
    return 0;
}