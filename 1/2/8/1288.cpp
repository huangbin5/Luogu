#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 25;
int n, a[maxn];

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < n; ++i)
        if (a[i] == 0)
            if (i & 1) {
                cout << "YES";
                return 0;
            } else
                break;
    for (int i = n - 1; i >= 0; --i)
        if (a[i] == 0) {
            if ((n - 1 - i) & 1)
                cout << "YES";
            else
                cout << "NO";
            return 0;
        }
    cout << (n & 1 ? "YES" : "NO");
    return 0;
}