#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

const int maxn = 100005;
int n, m;
struct Person {
    int direct;
    string job;
    Person() {}
};
Person person[maxn];

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i)
        cin >> person[i].direct >> person[i].job;
    int index = 0, direct, num;
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &direct, &num);
        if (person[index].direct ^ direct)
            index = (index + num) % n;
        else
            index = (index + n - num) % n;
    }
    cout << person[index].job;
    return 0;
}