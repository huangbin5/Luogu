#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 10, MOD = 10000;

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
            data[len++] = a % MOD;
            a /= MOD;
        }
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
} twon[85], dp[85][85];

int n, m, a[85][85];

// 打印bigint
ostream& operator<<(ostream& cout, const bigint& a) {
    for (int i = a.len - 1; i >= 0; --i)
        if (i == a.len - 1)
            cout << a[i];
        else
            cout << setw(4) << setfill('0') << a[i];
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

bigint max(const bigint& a, const bigint& b) { return (compare(a, b) > 0) ? a : b; }

// bigint + bigint
bigint add(const bigint& a, const bigint& b) {
    bigint c;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        int tmp = a[i] + b[i] + carry;
        c[c.len++] = tmp % MOD;
        carry = tmp / MOD;
    }
    // 最高位有进位
    if (carry)
        c[c.len++] = carry;
    return c;
}

bigint mul(const bigint& a, const bigint& b) {
    bigint c;
    // 两数相乘结果的长度只能为两数长度之和或减一
    c.len = a.len + b.len;
    for (int i = 0; i < a.len; ++i) {
        for (int j = 0; j < b.len; ++j) {
            // a[i] * b[j]的结果放在c[i + j]上，进位放在c[i + j + 1]上
            int tmp = a[i] * b[j] + c[i + j];
            c[i + j] = tmp % MOD;
            c[i + j + 1] += tmp / MOD;
        }
    }
    // 删除前导0，如果为0需要保留一个0
    while (c.len > 1 && c[c.len - 1] == 0)
        --c.len;
    return c;
}

void init_twon() {
    twon[1] = 2;
    for (int i = 2; i <= m; ++i)
        twon[i] = mul(twon[i - 1], 2);
}

void print_dp() {
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= m; ++j)
            cout << dp[i][j] << "\t";
        cout << endl;
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            cin >> a[i][j];
    init_twon();
    bigint ans = 0;
    for (int r = 1; r <= n; ++r) {
        for (int i = 1; i <= m; ++i)
            dp[i][i] = mul(a[r][i], twon[m]);
        for (int len = 2; len <= m; ++len)
            for (int i = 1, j = i + len - 1; j <= m; ++i, ++j)
                dp[i][j]
                    = max(add(dp[i][j - 1], mul(a[r][j], twon[m - j + i])), add(dp[i + 1][j], mul(a[r][i], twon[m - j + i])));
        // print_dp();
        ans = add(ans, dp[1][m]);
    }
    cout << ans;
    return 0;
}