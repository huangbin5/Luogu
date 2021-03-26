#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int k, n, a, b;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> n;
        int s = 0, cnt = 0;
        for (int i = 0; i < n / 2; ++i) {
            cin >> a >> b;
            if (a == 1)
                s ^= (!(b & 1));
            else if (b == 1)
                s ^= (!(a & 1));
            else if ((a & 1) ^ (b & 1))
                ++cnt;
            else if (a & 1)
                s ^= 0;
            else
                s ^= 1;
        }
        cout << ((cnt & 1) ? "YES" : (s ? "YES" : "NO")) << endl;
    }
    return 0;
}