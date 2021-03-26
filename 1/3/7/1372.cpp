#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

int n, k;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n >> k;
    cout << n / k;
    return 0;
}