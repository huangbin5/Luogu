#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 105;
int n, m;
bool vis[maxn] = { false };

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> m;
    int cnt = 0, cur = 0, num = 1;
    while (cnt < n) {
        cur = (cur + 1) % n;
        if (!vis[cur]) {
            ++num;
            if (num == m) {
                cout << (cur + 1) << " ";
                vis[cur] = true;
                ++cnt;
                num = 0;
            }
        }
    }
    return 0;
}