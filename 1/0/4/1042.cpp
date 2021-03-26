#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

const int maxn = 2505;
int line;
string res[maxn];

void handle(int type) {
    int a = 0, b = 0;
    for (int i = 0; i < line; ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            if (res[i][j] == 'W')
                ++a;
            else if (res[i][j] == 'L')
                ++b;
            else {
                cout << a << ":" << b << endl;
                return;
            }
            if ((a >= type && a - b >= 2) || (b >= type && b - a >= 2)) {
                cout << a << ":" << b << endl;
                a = b = 0;
            }
        }
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    for (line = 0;; ++line) {
        cin >> res[line];
        if (res[line].empty())
            break;
    }
    handle(11);
    cout << endl;
    handle(21);
    return 0;
}