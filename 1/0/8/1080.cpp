#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int n;
struct Hands {
    int left, right;
    Hands() {}
};
Hands hands[maxn];
// d[0]存放最低位，高位往后面加
struct BigInt {
    int d[maxn * 4];
    int len;
    BigInt() { init(); }
    BigInt(int a) {
        init();
        while (a > 0) {
            d[len++] = a % 10;
            a /= 10;
        }
    }
    BigInt(char* s) {
        init();
        len = strlen(s);
        for (int i = 0; i < len; ++i)
            d[len - 1 - i] = s[i] - '0';
    }
    void init() {
        memset(d, 0, sizeof(d));
        len = 0;
    }
    bool operator>(const BigInt& a) const {
        if (len != a.len)
            return len > a.len;
        for (int i = len - 1; i >= 0; --i)
            if (d[i] != a.d[i])
                return d[i] > a.d[i];
    }
};

BigInt mul(const BigInt& a, int b) {
    BigInt c;
    int carry = 0;
    for (int i = 0; i < a.len; ++i) {
        int tmp = a.d[i] * b + carry;
        c.d[c.len++] = tmp % 10;
        carry = tmp / 10;
    }
    // 可能有多位进位
    while (carry) {
        c.d[c.len++] = carry % 10;
        carry /= 10;
    }
    return c;
}

BigInt div(const BigInt& a, int b, int r = 0) {
    BigInt c;
    c.len = a.len;
    // 从高位开始
    for (int i = a.len - 1; i >= 0; --i) {
        r = r * 10 + a.d[i];
        c.d[i] = r / b;
        r %= b;
    }
    // 去除前导0
    while (c.len > 1 && c.d[c.len - 1] == 0)
        --c.len;
    return c;
}

ostream& operator<<(ostream& cout, const BigInt& a) {
    for (int i = a.len - 1; i >= 0; --i)
        cout << a.d[i];
    return cout;
}

bool cmp(Hands& a, Hands& b) { return 1.0 * a.left / b.right < 1.0 * b.left / a.right; }

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> hands[0].left >> hands[0].right;
    for (int i = 1; i <= n; ++i)
        cin >> hands[i].left >> hands[i].right;
    sort(hands + 1, hands + n + 1, cmp);
    BigInt ans = 0, product = 1, tmp;
    for (int i = 1; i <= n; ++i) {
        product = mul(product, hands[i - 1].left);
        tmp = div(product, hands[i].right);
        if (tmp > ans)
            ans = tmp;
    }
    cout << ans;
    return 0;
}