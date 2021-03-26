#include <cstdio>
#include <iostream>
using namespace std;
#define DEBUG

const int maxn = 105;
int n, num[maxn], avg, ans = 0;

void move(int start, int end) {
    if (start >= end)
        return;
    int idx, actualSum = 0, idealSum = 0;
    for (idx = start; idx <= end; actualSum += num[idx], idealSum += avg, ++idx) {
        if (actualSum <= idealSum && (actualSum + num[idx]) >= (idealSum + avg))
            break;
    }
    int trans = 0;
    // 左侧不够，拿一点给左侧
    if (actualSum < idealSum) {
        trans = (idealSum - actualSum);
        num[idx] -= trans;
        num[idx - 1] += trans;
        ++ans;
    }
    actualSum += (trans + num[idx]);
    idealSum += avg;
    // 右侧不够，拿一点给右侧
    if (actualSum > idealSum) {
        trans = (actualSum - idealSum);
        num[idx] -= trans;
        num[idx + 1] += trans;
        ++ans;
    }
    // 左侧右侧递归
    move(start, idx - 1);
    move(idx + 1, end);
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        scanf("%d", &num[i]);
        sum += num[i];
    }
    avg = sum / n;
    move(0, n - 1);
    cout << ans;
    return 0;
}