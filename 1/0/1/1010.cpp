#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
// #define DEBUG

int n;

void handle(int a) {
    // 递归基
    if (!a) {
        cout << 0;
        return;
    }
    int i = 0;
    while ((1 << (i + 1)) <= a)
        ++i;
    // 特判2^1
    if (i == 1)
        cout << 2;
    else {
        cout << "2(";
        handle(i);
        cout << ")";
    }
    if ((1 << i) < a) {
        cout << "+";
        handle(a - (1 << i));
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\data.in", "r", stdin);
    freopen("d:\\data.out", "w", stdout);
#endif
    cin >> n;
    handle(n);
    return 0;
}