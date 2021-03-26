#include <cstdio>
#include <iostream>
#include <stack>
#include <string>
using namespace std;
typedef long long ll;

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    string str;
    cin >> str;
    stack<int> s;
    int i = 0;
    while (str[i] != '@') {
        char c = str[i];
        if (c >= '0' && c <= '9') {
            int n = 0;
            while (str[i] != '.')
                n = n * 10 + (str[i++] - '0');
            s.push(n);
        } else {
            int a = s.top();
            s.pop();
            int b = s.top();
            s.pop();
            if (c == '+')
                s.push(a + b);
            else if (c == '-')
                s.push(b - a);
            else if (c == '*')
                s.push(a * b);
            else
                s.push(b / a);
        }
        ++i;
    }
    cout << s.top();
    return 0;
}