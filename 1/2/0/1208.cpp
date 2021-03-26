#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxm = 5005;
int n, m;
struct Nainong {
    int price, quantity;
    Nainong() {}
};
Nainong nainong[maxm];

bool cmp(Nainong& a, Nainong& b) { return a.price < b.price; }

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < m; ++i)
        cin >> nainong[i].price >> nainong[i].quantity;
    sort(nainong, nainong + m, cmp);
    int sum = 0, ans = 0;
    for (int i = 0; i < m; ++i) {
        if (sum + nainong[i].quantity >= n) {
            ans += (n - sum) * nainong[i].price;
            cout << ans;
            return 0;
        } else {
            sum += nainong[i].quantity;
            ans += nainong[i].quantity * nainong[i].price;
        }
    }
    cout << ans;
    return 0;
}