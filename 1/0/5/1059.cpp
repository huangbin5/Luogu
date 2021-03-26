#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

int n, flag[1005] = { 0 };

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    int a;
    for (int i = 0; i < n; ++i) {
        cin >> a;
        flag[a] = 1;
    }
    a = 0;
    for (int i = 0; i < 1005; ++i)
        if (flag[i])
            ++a;
    cout << a << endl;
    for (int i = 0; i < 1005; ++i)
        if (flag[i])
            cout << i << " ";
    return 0;
}