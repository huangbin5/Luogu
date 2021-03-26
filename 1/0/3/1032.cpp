#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
using namespace std;
typedef long long ll;
// #define DEBUG

int n = 0;
string s1, s2;
struct Rule {
    string s1, s2;
    Rule() {}
};
Rule rule[6];
struct Inter {
    int n;
    string s;
    Inter() {}
    Inter(int _n, string _s)
        : n(_n)
        , s(_s) {}
};
queue<Inter> q;
set<string> exist;

bool bfs() {
    q.push(Inter(0, s1));
    exist.insert(s1);
    while (!q.empty()) {
        Inter inter = q.front();
        q.pop();
        // 超过10次了
        if (inter.n > 10)
            return false;
        // 已是目标字符串
        if (inter.s == s2) {
            cout << inter.n;
            return true;
        }
        // 使用每个规则进行替换
        for (int i = 0; i < n; ++i) {
            int pos = -1;
            while ((pos = inter.s.find(rule[i].s1, pos + 1)) != string::npos) {
                string newStr = inter.s;
                newStr.replace(pos, rule[i].s1.size(), rule[i].s2);
                // 替换过则加入
                if (!exist.count(newStr)) {
                    q.push(Inter(inter.n + 1, newStr));
                    exist.insert(newStr);
                }
            }
        }
    }
    return false;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> s1 >> s2;
    while (cin >> rule[n].s1 >> rule[n].s2 && !rule[n].s1.empty())
        ++n;
    if (!bfs())
        cout << "NO ANSWER!";
    return 0;
}