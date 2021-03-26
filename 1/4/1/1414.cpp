#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 1e6 + 5;
int n, cnt[maxn] = { 0 };

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    int tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        int sq = sqrt(tmp);
        for (int j = 1; j <= sq; ++j)
            if (tmp % j == 0) {
                ++cnt[j];
                if (j * j != tmp)
                    ++cnt[tmp / j];
            }
    }
    int idx = maxn;
    for (int i = 1; i <= n; ++i) {
        while (cnt[idx] < i)
            --idx;
        cout << idx << endl;
    }
    return 0;
}