#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

const int maxn = 10005;
int n, inc, arr[maxn];

int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> inc;
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    for (int i = 0; i < inc; ++i)
        next_permutation(arr, arr + n);
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    return 0;
}