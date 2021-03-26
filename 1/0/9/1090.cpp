#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
// #define DEBUG

int n, ans = 0;
priority_queue<int, vector<int>, greater<int>> pq;

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    int tmp;
    for (int i = 0; i < n; ++i) {
        cin >> tmp;
        pq.push(tmp);
    }
    for (int i = 1; i < n; ++i) {
        tmp = pq.top();
        pq.pop();
        tmp += pq.top();
        pq.pop();
        pq.push(tmp);
        ans += tmp;
    }
    cout << ans;
    return 0;
}