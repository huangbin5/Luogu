#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1005;
int n;
struct Line {
    int id, time;
    Line() {}
};
Line arr[maxn];

bool cmp(Line& a, Line& b) { return a.time < b.time; }

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i) {
        arr[i].id = i + 1;
        cin >> arr[i].time;
    }
    sort(arr, arr + n, cmp);
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        if (i == n - 1)
            cout << arr[i].id << endl;
        else
            cout << arr[i].id << " ";
        total += arr[i].time * (n - i - 1);
    }
    cout << fixed << setprecision(2) << total * 1.0 / n;
    return 0;
}