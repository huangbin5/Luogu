#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

int n;
struct Person {
    int id;
    string score;
    Person() {}
};
Person person[25];

bool cmp(Person& a, Person& b) {
    if (a.score.size() != b.score.size())
        return a.score.size() > b.score.size();
    for (int i = 0; i < a.score.size(); ++i) {
        if (a.score[i] != b.score[i])
            return a.score[i] > b.score[i];
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i) {
        person[i].id = i + 1;
        cin >> person[i].score;
    }
    sort(person, person + n, cmp);
    cout << person[0].id << endl << person[0].score;
    return 0;
}