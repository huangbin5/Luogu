#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct People {
    int id;
    bool deleted;
    People *left, *right;
    People() {
        id = 0;
        deleted = false;
        left = right = NULL;
    }
    People(int _id, People* _left = NULL, People* _right = NULL, bool _deleted = false)
        : id(_id)
        , left(_left)
        , right(_right)
        , deleted(_deleted) {}
};

const int maxn = 100005;
int n, m;
People p[maxn];

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    p[1].id = 1;
    p[0].right = &p[1];
    p[1].right = &p[n + 1];
    p[1].left = &p[0];
    p[n + 1].left = &p[1];
    int id, direct;
    for (int i = 2; i <= n; ++i) {
        p[i].id = i;
        cin >> id >> direct;
        // 将i放在id的左边
        if (direct == 0) {
            p[i].left = p[id].left;
            p[i].right = &p[id];
            p[id].left->right = &p[i];
            p[id].left = &p[i];
        } else {
            p[i].left = &p[id];
            p[i].right = p[id].right;
            p[id].right->left = &p[i];
            p[id].right = &p[i];
        }
    }
    cin >> m;
    for (int i = 0; i < m; ++i) {
        cin >> id;
        p[id].deleted = true;
    }
    for (People* i = p[0].right; i != &p[n + 1]; i = i->right)
        if (!i->deleted)
            cout << i->id << " ";
    return 0;
}