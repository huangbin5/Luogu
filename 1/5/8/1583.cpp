#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 20005;
int n, k, add[10];
struct Person {
    int id, weight;
    Person() {}
};
Person person[maxn];

bool cmp(Person& a, Person& b) {
    if (a.weight != b.weight)
        return a.weight > b.weight;
    return a.id < b.id;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> k;
    for (int i = 0; i < 10; ++i)
        cin >> add[i];
    for (int i = 0; i < n; ++i) {
        cin >> person[i].weight;
        person[i].id = i + 1;
    }
    sort(person, person + n, cmp);
    for (int i = 0; i < n; ++i)
        person[i].weight += add[i % 10];
    sort(person, person + n, cmp);
    for (int i = 0; i < k; ++i)
        cout << person[i].id << " ";
    return 0;
}