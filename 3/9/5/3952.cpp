#include <algorithm>
#include <cstdio>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
using namespace std;
// #define DEBUG

const int maxn = 105;
int m, n, complexInt, curLine, ans;
string complexStr, code[maxn];
set<char> var;

void handleComplex() {
    if (complexStr[2] == '1')
        complexInt = 0;
    else
        sscanf(complexStr.c_str(), "O(n^%d)", &complexInt);
}

int handle() {
    // 没有与'E'配对的'F'
    if (code[curLine][0] == 'E')
        return -1;
    char x;
    string a, b;
    stringstream ss(code[curLine]);
    ss >> x >> x >> a >> b;
    // 变量已存在
    if (var.count(x))
        return -1;
    var.insert(x);
    // 递归嵌套循环
    ++curLine;
    if (curLine >= n)
        return -1;
    int recur = 0;
    while (curLine < n && code[curLine][0] == 'F') {
        int tmpRecur = handle();
        if (tmpRecur == -1)
            return -1;
        recur = max(recur, tmpRecur);
    }
    // 跳过与该循环配对的'E'
    ++curLine;
    if (curLine > n)
        return -1;
    var.erase(x);
    // 计算当前循环的时间复杂度
    if (a[0] == 'n' && b[0] == 'n')
        return recur;
    if (a[0] == 'n' && b[0] != 'n')
        return 0;
    if (a[0] != 'n' && b[0] == 'n')
        return 1 + recur;
    int aa, bb;
    sscanf(a.c_str(), "%d", &aa);
    sscanf(b.c_str(), "%d", &bb);
    if (aa <= bb)
        return recur;
    else
        return 0;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> m;
    for (int i = 0; i < m; ++i) {
        var.clear();
        // 输入
        cin >> n >> complexStr;
        cin.ignore();
        // 题目所给的时间复杂度
        handleComplex();
        // 输入
        for (int j = 0; j < n; ++j)
            getline(cin, code[j]);
        // 奇数行
        if (n % 2) {
            cout << "ERR" << endl;
            continue;
        }
        ans = -1;
        curLine = 0;
        int tmpAns = 0;
        // 从第0行开始处理
        while (curLine < n) {
            tmpAns = handle();
            // 语法错误
            if (tmpAns == -1)
                break;
            ans = max(ans, tmpAns);
        }
        if (tmpAns == -1)
            cout << "ERR" << endl;
        else if (ans == complexInt)
            cout << "Yes" << endl;
        else
            cout << "No" << endl;
    }
    return 0;
}