#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
// #define DEBUG

map<string, int> digitMap;
int nums[10], numCnt = 0;

void init() {
    string s[20] = { "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve",
        "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty" };
    for (int i = 0; i < 20; ++i)
        digitMap[s[i]] = i + 1;
    digitMap["a"] = digitMap["another"] = digitMap["first"] = 1;
    digitMap["both"] = digitMap["second"] = 2;
    digitMap["third"] = 3;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    init();
    string s;
    for (int i = 0; i < 6; ++i) {
        cin >> s;
        if (s[s.size() - 1] == '.')
            s.erase(s.size() - 1);
        if (digitMap.count(s))
            nums[numCnt++] = digitMap[s] * digitMap[s] % 100;
    }
    sort(nums, nums + numCnt);
    long long res = 0;
    for (int i = 0; i < numCnt; ++i)
        res = res * 100 + nums[i];
    cout << res;
    return 0;
}