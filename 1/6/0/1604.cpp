#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 2005;
int base;

// d[0]存放最低位，高位往后面加
struct bigint {
    int len;
    char data[maxn];
    bigint() { init(); }
    // 字符数组
    bigint(const char* s) {
        init();
        len = strlen(s);
        for (int i = 0; i < len; ++i)
            data[len - 1 - i] = s[i];
    }
    void init() {
        len = 0;
        for (int i = 0; i < maxn; ++i)
            data[i] = '0';
    }
};

int toNum(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';
    return c - 'A' + 10;
}

int toChar(int n) {
    if (n >= 0 && n <= 9)
        return n + '0';
    return n - 10 + 'A';
}

// bigint + bigint
bigint add(const bigint& a, const bigint& b) {
    bigint c;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        int tmp = toNum(a.data[i]) + toNum(b.data[i]) + carry;
        c.data[c.len++] = toChar(tmp % base);
        carry = tmp / base;
    }
    // 最高位有进位
    if (carry)
        c.data[c.len++] = toChar(carry);
    return c;
}

// 打印bigint
ostream& operator<<(ostream& cout, const bigint& a) {
    for (int i = a.len - 1; i >= 0; --i)
        cout << a.data[i];
    return cout;
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> base;
    string s;
    cin >> s;
    bigint a(s.c_str());
    cin >> s;
    bigint b(s.c_str());
    cout << add(a, b);
    return 0;
}