#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

vector<int> s;

void dfs(int pre, int left) {
    if (left == 0 && s.size() > 1) {
        for (int i = 0; i < s.size(); ++i) {
            if (i)
                cout << '+';
            cout << s[i];
        }
        cout << endl;
        return;
    }
    for (int cur = pre; cur <= left; ++cur) {
        s.push_back(cur);
        dfs(cur, left - cur);
        s.pop_back();
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int n;
    cin >> n;
    dfs(1, n);
    return 0;
}