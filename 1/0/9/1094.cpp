#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 30005;
int w, n, value[maxn];

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> w >> n;
    for (int i = 0; i < n; ++i)
        cin >> value[i];
    sort(value, value + n);
    int ans = 0, left = 0, right = n - 1;
    while (left <= right) {
        ++ans;
        if (left == right)
            break;
        if (value[right] + value[left] <= w)
            ++left;
        --right;
    }
    cout << ans;
    return 0;
}