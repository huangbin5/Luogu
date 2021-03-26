#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int BASE = 100000000, WIDTH = 8;

// d[0]存放最低位，高位往后面加
struct bigint {
    int len, data[3005];
    bigint() { init(); }
    // 整数
    bigint(ll a) {
        init();
        // 特殊情况0
        if (a == 0)
            len = 1;
        while (a > 0) {
            data[len++] = a % BASE;
            a /= BASE;
        }
    }
    // 字符数组
    bigint(const char* s) {
        init();
        int slen = strlen(s);
        for (int i = slen - 1; i >= 0; i -= WIDTH) {
            data[len] = 0;
            for (int j = max(i - WIDTH + 1, 0); j <= i; ++j)
                data[len] = data[len] * 10 + s[j] - '0';
            ++len;
        }
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

// 比较两个bigint的大小
int compare(const bigint& a, const bigint& b) {
    if (a.len > b.len)
        return 1;
    else if (a.len < b.len)
        return -1;
    for (int i = a.len - 1; i >= 0; --i)
        if (a.data[i] > b.data[i])
            return 1;
        else if (a.data[i] < b.data[i])
            return -1;
    return 0;
}

// 大bigint - 小bigint
bigint sub(const bigint& a, const bigint& b) {
    bigint c;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        int tmp = a.data[i] - b.data[i] - carry + BASE;
        c.data[c.len++] = tmp % BASE;
        carry = (tmp / BASE) ^ 1;
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c.data[c.len - 1] == 0)
        --c.len;
    return c;
}

bigint mul2(const bigint& a) {
    bigint c;
    int b = 2, carry = 0;
    for (int i = 0; i < a.len; ++i) {
        int tmp = a.data[i] * b + carry;
        c.data[c.len++] = tmp % BASE;
        carry = tmp / BASE;
    }
    // 可能有多位进位
    while (carry) {
        c.data[c.len++] = carry % BASE;
        carry /= BASE;
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c.data[c.len - 1] == 0)
        --c.len;
    return c;
}

// r为余数
bigint div2(const bigint& a) {
    bigint c;
    int b = 2, r = 0;
    c.len = a.len;
    // 从高位开始
    for (int i = a.len - 1; i >= 0; --i) {
        int tmp = r * BASE + a.data[i];
        c.data[i] = tmp / b;
        r = tmp % b;
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c.data[c.len - 1] == 0)
        --c.len;
    return c;
}

int cnt = 0;

bigint gcd(bigint a, bigint b) {
    int sign = compare(a, b);
    while (sign != 0) {
        if (a.data[0] & 1) {
            if (b.data[0] & 1)
                if (sign > 0)
                    a = sub(a, b);
                else
                    b = sub(b, a);
            else
                b = div2(b);
        } else {
            if (b.data[0] & 1)
                a = div2(a);
            else {
                a = div2(a);
                b = div2(b);
                ++cnt;
            }
        }
        sign = compare(a, b);
    }
    for (int i = 0; i < cnt; ++i)
        a = mul2(a);
    cout << a;
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    string s1, s2;
    cin >> s1 >> s2;
    bigint a(s1.c_str()), b(s2.c_str());
    gcd(a, b);
    return 0;
}