#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

int n, m;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    int tmp, sum = 0, ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        if (sum + tmp > m) {
            ++ans;
            sum = 0;
            if (tmp <= m)
                sum = tmp;
        } else
            sum += tmp;
    }
    cout << ans + 1;
    return 0;
}