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
    // 小bigint - 大bigint不处理
    if (compare(a, b) >= 0) {
        int carry = 0;
        for (int i = 0; i < a.len || i < b.len; ++i) {
            int tmp = a.data[i] - b.data[i] - carry + 10;
            c.data[c.len++] = tmp % 10;
            carry = (tmp / 10) ^ 1;
        }
        // 删除前导0，如果为0需要保留一个0
        while (c.len > 1 && c.data[c.len - 1] == 0)
            --c.len;
    }
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
    if (compare(a, b) >= 0)
        cout << sub(a, b);
    else
        cout << "-" << sub(b, a);
    return 0;
}