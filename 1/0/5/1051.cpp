#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
// #define DEBUG

const int maxn = 105;
int n, total = 0;
struct Student {
    string name;
    int id, eaxmScore, classScore, paper;
    char isServant, isWestern;
    int money;
    Student() {}
};
Student student[maxn];

bool cmp(Student& a, Student& b) {
    if (a.money != b.money)
        return a.money > b.money;
    return a.id < b.id;
}

void caculate(Student& a) {
    // 8000: 期末>80, 论文>0
    if (a.eaxmScore > 80 && a.paper > 0)
        a.money += 8000;
    // 4000: 期末>85, 班级>80
    if (a.eaxmScore > 85 && a.classScore > 80)
        a.money += 4000;
    // 2000: 期末>90
    if (a.eaxmScore > 90)
        a.money += 2000;
    // 1000: 期末>85, 西部
    if (a.eaxmScore > 85 && a.isWestern == 'Y')
        a.money += 1000;
    // 850: 班级>80, 干部
    if (a.classScore > 80 && a.isServant == 'Y')
        a.money += 850;
    total += a.money;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Student& stu = student[i];
        cin >> stu.name >> stu.eaxmScore >> stu.classScore >> stu.isServant >> stu.isWestern >> stu.paper;
        stu.id = i;
        stu.money = 0;
        caculate(stu);
    }
    sort(student, student + n, cmp);
    cout << student[0].name << endl << student[0].money << endl << total;
    return 0;
}