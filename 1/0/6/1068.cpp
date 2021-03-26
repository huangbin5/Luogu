#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 5005;
int n, m;
struct Person {
    int id, score;
    Person() {}
};
Person person[maxn];

int cmp(Person& a, Person& b) {
    if (a.score != b.score)
        return a.score > b.score;
    return a.id < b.id;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> m;
    for (int i = 0; i < n; ++i)
        cin >> person[i].id >> person[i].score;
    sort(person, person + n, cmp);
    int idx = m * 3 / 2, line = idx - 1;
    while (person[idx].score == person[line].score)
        ++idx;
    cout << person[line].score << " " << idx << endl;
    for (int i = 0; i < idx; ++i)
        cout << person[i].id << " " << person[i].score << endl;
    return 0;
}