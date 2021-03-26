#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

int n;

void handle(int a, int b) {
    if (a == 0)
        return;
    //符号
    if (a < 0)
        cout << "-";
    else if (b != n)
        cout << "+";
    //系数
    if (abs(a) != 1 || b == 0)
        cout << abs(a);
    //指数
    if (b != 0) {
        cout << "x";
        if (b != 1)
            cout << "^" << b;
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int tmp;
    for (int i = n; i >= 0; --i) {
        scanf("%d", &tmp);
        handle(tmp, i);
    }
    return 0;
}