#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

const int maxn = 25;
int n[4], a[4][maxn], b[4] = { 0 }, ans[4];

void dfs(int idx1, int idx2, int sum_select, int sum_remain) {
    if (sum_select + a[idx1][idx2] > b[idx1] / 2) {
        sum_remain = b[idx1] - sum_select;
        ans[idx1] = min(ans[idx1], min(max(sum_select, sum_remain), max(sum_select + a[idx1][idx2], sum_remain - a[idx1][idx2])));
        return;
    }
    sum_select += a[idx1][idx2];
    for (int i = idx2 + 1; i < n[idx1]; ++i) {
        dfs(idx1, i, sum_select, sum_remain);
        sum_remain += a[idx1][i];
        if (sum_remain > b[idx1] / 2)
            break;
    }
}

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    for (int i = 0; i < 4; ++i) {
        cin >> n[i];
        ans[i] = 1e5;
    }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < n[i]; ++j) {
            cin >> a[i][j];
            b[i] += a[i][j];
        }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < n[i]; ++j)
            dfs(i, j, 0, 0);
    cout << ans[0] + ans[1] + ans[2] + ans[3];
    return 0;
}