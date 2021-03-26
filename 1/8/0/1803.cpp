#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1e6 + 5;
int n;
struct Contest {
    int start, end;
    Contest() {}
};
Contest contest[maxn];

bool cmp(Contest& a, Contest& b) { return a.end < b.end; }

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> contest[i].start >> contest[i].end;
    sort(contest, contest + n, cmp);
    int curTime = 0, idx = 0, ans = 0;
    while (idx < n) {
        if (contest[idx].start >= curTime) {
            ++ans;
            curTime = contest[idx].end;
        }
        ++idx;
    }
    cout << ans;
    return 0;
}