#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Hand {
    ll left, right;
    Hand() { left = right = 0; }
    bool operator<(Hand& a) { return left + max(right, a.left) + a.right < a.left + max(a.right, left) + right; }
};

const int maxn = 20005;
int k, n;
Hand hand[maxn];

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> n;
        ll leftSum = 0, rightSum = 0, ans = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> hand[i].left >> hand[i].right;
            rightSum += hand[i].right;
        }
        sort(hand + 1, hand + n + 1);
        for (int i = 1; i <= n; ++i)
            cout << hand[i].left << " " << hand[i].right << endl;
        for (int i = 1; i <= n; ++i) {
            leftSum += hand[i].left;
            rightSum -= hand[i - 1].right;
            ans = max(ans, leftSum + rightSum);
        }
        cout << ans << endl << endl;
    }
    return 0;
}