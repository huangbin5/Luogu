#include <cstdio>
#include <iostream>
#include <map>
#include <string>
using namespace std;
// #define DEBUG

map<char, char> encode, decode;
string origin, tackle, target, ans = "";

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> tackle >> origin >> target;
    for (int i = 0; i < origin.size(); ++i) {
        if (encode.count(origin[i])) {
            // 相同的原码对应不同的密码
            if (encode[origin[i]] != tackle[i]) {
                cout << "Failed";
                return 0;
            }
        } else {
            encode[origin[i]] = tackle[i];
            // 相同的密码对应不同的原码
            if (decode.count(tackle[i])) {
                cout << "Failed";
                return 0;
            } else
                decode[tackle[i]] = origin[i];
        }
    }
    if (encode.size() == 26) {
        for (int i = 0; i < target.size(); ++i)
            ans += decode[target[i]];
        cout << ans;
    } else
        cout << "Failed";
    return 0;
}