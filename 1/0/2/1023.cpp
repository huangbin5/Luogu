#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 100005;
int expectPrice, factoryPrice, factoryAmount, decreaseAmount, saleAmount[maxn];

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d%d", &expectPrice, &factoryPrice, &factoryAmount);
    saleAmount[factoryPrice] = factoryAmount;
    int price, amount, prePrice = factoryPrice, preAmount = factoryAmount, increase;
    while (scanf("%d%d", &price, &amount) && price != -1 && amount != -1) {
        saleAmount[price] = amount;
        // 计算相邻价位间的销量
        increase = (amount - preAmount) / (price - prePrice);
        for (int i = prePrice + 1; i < price; ++i)
            saleAmount[i] = saleAmount[i - 1] + increase;
        prePrice = price;
        preAmount = amount;
    }
    scanf("%d", &decreaseAmount);
    // 计算后续价位的销量
    while (saleAmount[prePrice] - decreaseAmount > 0) {
        saleAmount[prePrice + 1] = saleAmount[prePrice] - decreaseAmount;
        ++prePrice;
    }
    int maxAns = maxn, minAns = -maxn;
    // 先计算要比低于预期价盈利更多的补贴范围
    for (price = factoryPrice + 1; price < expectPrice; ++price)
        maxAns = min(maxAns,
            (int)floor(((price - factoryPrice) * saleAmount[price] - (expectPrice - factoryPrice) * saleAmount[expectPrice]) * 1.0
                / (saleAmount[expectPrice] - saleAmount[price])));
    // 再计算要比高于预期价盈利更多的补贴范围
    for (price = prePrice; price > expectPrice; --price)
        minAns = max(minAns,
            (int)ceil(((price - factoryPrice) * saleAmount[price] - (expectPrice - factoryPrice) * saleAmount[expectPrice]) * 1.0
                / (saleAmount[expectPrice] - saleAmount[price])));
    if (maxAns < minAns)
        cout << "NO SOLUTION";
    else if (maxAns < 0)
        cout << maxAns;
    else if (minAns > 0)
        cout << minAns;
    else
        cout << 0;
    return 0;
}