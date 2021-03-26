#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int sum;
vector<pair<int, int>> ans;

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> sum;
    for (int i = 1; i <= sum / 2; ++i) {
        if (sum % i)
            continue;
        // i个j
        int j = sum / i;
        if ((i != 1) && (i & 1) && (j - (i >> 1) >= 1))
            ans.push_back(make_pair(j - (i >> 1), j + (i >> 1)));
        if ((j & 1) && ((j >> 1) - i >= 0))
            ans.push_back(make_pair((j >> 1) - i + 1, (j >> 1) + i));
    }
    sort(ans.begin(), ans.end());
    for (vector<pair<int, int>>::iterator it = ans.begin(); it != ans.end(); ++it)
        cout << it->first << " " << it->second << endl;
    return 0;
}