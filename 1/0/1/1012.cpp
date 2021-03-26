#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

int n;
string num[20];

bool cmp(string& a, string& b) { return a + b > b + a; }

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> num[i];
    sort(num, num + n, cmp);
    for (int i = 0; i < n; ++i)
        cout << num[i];
    return 0;
}