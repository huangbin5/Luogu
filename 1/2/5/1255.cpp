#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 5005;

// d[0]存放最低位，高位往后面加
struct bigint {
    int len, data[2000];
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

// 大bigint - 小bigint
bigint sub(const bigint& a, const bigint& b) {
    bigint c;
    // 小bigint - 大bigint不处理
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        int tmp = a.data[i] - b.data[i] - carry + 10;
        c.data[c.len++] = tmp % 10;
        carry = (tmp / 10) ^ 1;
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c.data[c.len - 1] == 0)
        --c.len;
    return c;
}

int n;
bigint pre = 1, ans = 1;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 2; i <= n; ++i) {
        ans = add(pre, ans);
        pre = sub(ans, pre);
    }
    if (n < 1)
        cout << 0;
    else
        cout << ans;
    return 0;
}