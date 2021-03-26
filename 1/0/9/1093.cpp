#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 305;
int n;
struct Student {
    int id, chinese, math, english, total;
    Student() {}
};
Student student[maxn];

bool cmp(Student& a, Student& b) {
    if (a.total != b.total)
        return a.total > b.total;
    if (a.chinese != b.chinese)
        return a.chinese > b.chinese;
    return a.id < b.id;
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Student& stu = student[i];
        cin >> stu.chinese >> stu.math >> stu.english;
        stu.id = i + 1;
        stu.total = stu.chinese + stu.math + stu.english;
    }
    sort(student, student + n, cmp);
    for (int i = 0; i < 5; ++i)
        cout << student[i].id << " " << student[i].total << endl;
    return 0;
}