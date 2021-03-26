#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

int p1, p2, p3;
string s;
int startPos = 0, pos;

void fillStar() {
    for (int i = s[pos - 1] + 1; i < s[pos + 1]; ++i)
        for (int j = 0; j < p2; ++j)
            cout << "*";
}

void handle() {
    if (pos == s.size() - 1) {
        cout << s[pos];
        return;
    }
    if (s[pos - 1] >= s[pos + 1])
        cout << s[pos];
    else if (isalpha(s[pos - 1]) && isalpha(s[pos + 1])) {
        if (p1 == 3)
            fillStar();
        else {
            char startAlpha, endAlpha;
            if (p3 == 1) {
                if (p1 == 1) {
                    startAlpha = s[pos - 1];
                    endAlpha = s[pos + 1];
                } else {
                    startAlpha = s[pos - 1] + 'A' - 'a';
                    endAlpha = s[pos + 1] + 'A' - 'a';
                }
                for (char i = startAlpha + 1; i < endAlpha; ++i)
                    for (int j = 0; j < p2; ++j)
                        cout << i;
            } else {
                if (p1 == 1) {
                    startAlpha = s[pos + 1];
                    endAlpha = s[pos - 1];
                } else {
                    startAlpha = s[pos + 1] + 'A' - 'a';
                    endAlpha = s[pos - 1] + 'A' - 'a';
                }
                for (char i = startAlpha - 1; i > endAlpha; --i)
                    for (int j = 0; j < p2; ++j)
                        cout << i;
            }
        }
    } else if (isdigit(s[pos - 1]) && isdigit(s[pos + 1])) {
        if (p1 == 3)
            fillStar();
        else {
            char startAlpha, endAlpha;
            if (p3 == 1) {
                startAlpha = s[pos - 1];
                endAlpha = s[pos + 1];
                for (char i = startAlpha + 1; i < endAlpha; ++i)
                    for (int j = 0; j < p2; ++j)
                        cout << i;
            } else {
                startAlpha = s[pos + 1];
                endAlpha = s[pos - 1];
                for (char i = startAlpha - 1; i > endAlpha; --i)
                    for (int j = 0; j < p2; ++j)
                        cout << i;
            }
        }
    } else
        cout << s[pos];
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> p1 >> p2 >> p3 >> s;
    while ((pos = s.find('-', startPos)) != string::npos) {
        if (pos != startPos) {
            cout << s.substr(startPos, pos - startPos);
            handle();
        } else
            cout << s[startPos];
        startPos = pos + 1;
    }
    cout << s.substr(startPos);
    return 0;
}