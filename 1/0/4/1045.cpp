#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef complex<double> cd;
const double PI = acos(-1.0);

struct bigint {
    int len, data[1005];
    bigint() { init(); }
    bigint(ll a) {
        init();
        if (a == 0)
            len = 1;
        while (a > 0) {
            data[len++] = a % 10;
            a /= 10;
        }
    }
    void init() {
        memset(data, 0, sizeof(data));
        len = 0;
    }
};

bigint sub(const bigint& a, const bigint& b) {
    bigint c;
    int carry = 0;
    for (int i = 0; i < a.len || i < b.len; ++i) {
        int tmp = a.data[i] - b.data[i] - carry + 10;
        c.data[c.len++] = tmp % 10;
        carry = (tmp / 10) ^ 1;
    }
    while (c.len > 1 && c.data[c.len - 1] == 0)
        --c.len;
    return c;
}

void fft(vector<cd>& v, bool inverse) {
    int len = v.size();
    for (int idx = 0, anti = 0; idx < len; idx++) {
        if (anti > idx)
            swap(v[idx], v[anti]);
        int test = len;
        while (anti & (test >>= 1))
            anti &= ~test;
        anti |= test;
    }
    double pi = inverse ? -PI : PI;
    for (int half = 1; half < len; half <<= 1) {
        cd w1 = exp(cd(0, pi / half));
        for (int start = 0; start < len; start += (half << 1)) {
            cd w = 1;
            for (int cur = start; cur < start + half; ++cur) {
                cd x = v[cur];
                cd y = w * v[cur + half];
                v[cur] = x + y;
                v[cur + half] = x - y;
                w *= w1;
            }
        }
    }
    if (inverse)
        for (int i = 0; i < len; ++i)
            v[i] /= len;
}

bigint mul_fft(const bigint& a, const bigint& b) {
    bigint c;
    c.len = 2;
    while (c.len < a.len + b.len)
        c.len <<= 1;
    vector<cd> v1(c.len, 0), v2(c.len, 0);
    for (int i = 0; i < a.len; ++i)
        v1[i] = a.data[i];
    for (int i = 0; i < b.len; ++i)
        v2[i] = b.data[i];
    fft(v1, false);
    fft(v2, false);
    for (int i = 0; i < c.len; ++i)
        v1[i] *= v2[i];
    fft(v1, true);
    for (int i = 0; i < c.len; ++i) {
        int tmp = c.data[i] + (int)(v1[i].real() + 0.5);
        c.data[i] = tmp % 10;
        c.data[i + 1] = tmp / 10;
    }
    while (c.len > 1 && c.data[c.len - 1] == 0)
        --c.len;
    return c;
}

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

bigint operator<<(const bigint& a, int n) {
    bigint c;
    for (int i = a.len - 1; i >= 0; --i)
        c.data[i + n] = a.data[i];
    for (int i = 0; i < n; ++i)
        c.data[i] = 0;
    c.len = a.len + n;
    return c;
}

bigint& operator>>=(bigint& a, int n) {
    a.len -= n;
    for (int i = 0; i < a.len; ++i)
        a.data[i] = a.data[i + n];
    for (int i = a.len; i < a.len + n; ++i)
        a.data[i] = 0;
    return a;
}

bigint div_high(const bigint& a, const bigint& b, bigint& r) {
    r = a;
    if (compare(a, b) < 0)
        return 0ll;
    bigint tb = b << (a.len - b.len), c;
    c.len = a.len - b.len + 1;
    for (int i = c.len - 1; i >= 0; --i) {
        while (compare(r, tb) >= 0) {
            ++c.data[i];
            r = sub(r, tb);
        }
        tb >>= 1;
    }
    if (c.data[c.len - 1] == 0)
        --c.len;
    return c;
}

ostream& operator<<(ostream& cout, const bigint& a) {
    for (int i = 9; i >= 0; --i) {
        for (int j = 49; j >= 0; --j) {
            int idx = i * 50 + j;
            if (idx == 0)
                cout << a.data[idx] - 1;
            else if (idx >= a.len)
                cout << 0;
            else
                cout << a.data[idx];
        }
        cout << endl;
    }
    return cout;
}

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int n;
    cin >> n;
    cout << ceil(n * log10(2)) << endl;
    bigint ans = 1, tmp = 2, mod;
    mod.len = 501;
    mod.data[500] = 1;
    while (n) {
        if (n & 1)
            div_high(mul_fft(ans, tmp), mod, ans);
        n >>= 1;
        div_high(mul_fft(tmp, tmp), mod, tmp);
    }
    cout << ans;
    return 0;
}