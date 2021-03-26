#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
typedef long long ll;

string s;

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> s;
    int cnt = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(')
            ++cnt;
        if (s[i] == ')') {
            --cnt;
            if (cnt < 0) {
                cout << "NO";
                return 0;
            }
        }
    }
    cout << (cnt ? "NO" : "YES");
    return 0;
}