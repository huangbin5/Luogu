#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

int n, col[15] = { 0 }, ans = 0;
int a[30] = { 0 }, b[15] = { 0 }, c[30] = { 0 };

// bool check(int row) {
//     for (int i = 1; i < row; ++i)
//         // 检查列、主对角线、副对角线
//         if (col[i] == col[row] || col[i] - i == col[row] - row || col[i] + i == col[row] + row)
//             return false;
//     return true;
// }

void setRow(int row) {
    if (row == n + 1) {
        ans++;
        if (ans <= 3)
            for (int i = 1; i <= n; ++i)
                if (i == n)
                    cout << col[i] << endl;
                else
                    cout << col[i] << " ";
    } else
        for (int i = 1; i <= n; ++i) {
            // if (check(row))
            /**
             * 如果使用check方法判断，则每次check最多需要循环row次，约为n/2，会超时！！！
             */
            if (!a[row - i + n] && !b[i] && !c[row + i]) {
                col[row] = i;
                a[row - i + n] = 1;
                b[i] = 1;
                c[row + i] = 1;
                setRow(row + 1);
                a[row - i + n] = 0;
                b[i] = 0;
                c[row + i] = 0;
            }
        }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    setRow(1);
    cout << ans;
    return 0;
}