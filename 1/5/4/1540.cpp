#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
using namespace std;
// #define DEBUG

int m, n, ans = 0;
queue<int> q;
set<int> s;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &m, &n);
    int tmp;
    while (n > 0) {
        --n;
        scanf("%d", &tmp);
        if (s.count(tmp) != 0)
            continue;
        ++ans;
        if (q.size() == m) {
            int top = q.front();
            s.erase(top);
            q.pop();
        }
        q.push(tmp);
        s.insert(tmp);
    }
    cout << ans << endl;
    return 0;
}