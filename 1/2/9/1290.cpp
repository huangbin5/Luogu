#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

int k, n, m;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> n >> m;
        int cnt = 0;
        while (n != m && n != 1 && m != 1) {
            if (n < m)
                swap(n, m);
            if (n / m > 1)
                break;
            n -= m;
            ++cnt;
        }
        cout << ((cnt & 1) ? "Ollie wins" : "Stan wins") << endl;
    }
    return 0;
}