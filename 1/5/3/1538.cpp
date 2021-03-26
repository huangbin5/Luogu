#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
#define DEBUG

/**
 * 如若大小为k，则一个数字的宽度为k+2，高度为2k+3，中间的那行为第k+1行
 */
int k;
string s;

void pkchar(char c) {
    for (int i = 0; i < k; ++i)
        cout << c;
}

void output(int row, int num) {
    // 第0行
    // 02356789: '-'
    // 14: ' '
    if (row == 0) {
        cout << ' ';
        if (num == 1 || num == 4)
            pkchar(' ');
        else
            pkchar('-');
        cout << ' ';
    }
    // 第1~k行
    // 0489: '|'+'|'
    // 1237: ' '+'|'
    // 56: '|'+' '
    if (row > 0 && row < k + 1) {
        if (num == 1 || num == 2 || num == 3 || num == 7)
            cout << ' ';
        else
            cout << '|';
        pkchar(' ');
        if (num == 5 || num == 6)
            cout << ' ';
        else
            cout << '|';
    }
    // 第k+1行
    // 017: ' '
    // 2345689: '-'
    if (row == k + 1) {
        cout << ' ';
        if (num == 0 || num == 1 || num == 7)
            pkchar(' ');
        else
            pkchar('-');
        cout << ' ';
    }
    // 第k+2~2k+1行
    // 068: '|'+'|'
    // 134579: ' '+'|'
    // 2: '|'+' '
    if (row > k + 1 && row < 2 * k + 2) {
        if (num == 0 || num == 2 || num == 6 || num == 8)
            cout << '|';
        else
            cout << ' ';
        pkchar(' ');
        if (num == 2)
            cout << ' ';
        else
            cout << '|';
    }
    // 第2k+2行
    // 0235689: '-';
    // 147: ' '
    if (row == 2 * k + 2) {
        cout << ' ';
        if (num == 1 || num == 4 || num == 7)
            pkchar(' ');
        else
            pkchar('-');
        cout << ' ';
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> k >> s;
    // 一行一行输出
    for (int i = 0; i < 2 * k + 3; ++i) {
        // 一个数字一个数字输出
        for (int j = 0; j < s.size(); ++j) {
            if (j != 0)
                cout << ' ';
            output(i, s[j] - '0');
        }
        cout << endl;
    }
    return 0;
}