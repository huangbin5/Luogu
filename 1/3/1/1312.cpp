#include <cstdio>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
#define idx(x, y) ((x) * (maxy)) + (y)
#define index idx((x), (y))

struct Step {
    int x, y, direct;
    Step() {}
    Step(int _x, int _y, int _direct)
        : x(_x)
        , y(_y)
        , direct(_direct) {}
};

struct Node {
    string status;
    vector<Step> step;
    Node() {}
    Node(string _status, vector<Step> _step = vector<Step>())
        : status(_status)
        , step(_step) {}
};

// 行和列和数组的相反
const int maxx = 5, maxy = 7;
int n;
string status = "", newStatus, target(35, '0');
set<string> exist;
bool flag[maxx][maxy] = { false };

char toChar(int i) { return i == 10 ? 'a' : '0' + i; }

bool valid(int x, int y, int direct) {
    if (direct == 1 && x == maxx - 1)
        return false;
    if (direct == -1 && x == 0)
        return false;
    if (status[index] == status[idx(x + direct, y)])
        return false;
    return status[index] != '0';
}

void adjust() {
    // 降落每一列
    for (int x = 0; x < maxx; ++x) {
        int cury = 0;
        for (int y = 0; y < maxy; ++y) {
            if (newStatus[index] != '0')
                newStatus[idx(x, cury++)] = newStatus[index];
        }
        for (; cury < maxy; ++cury)
            newStatus[idx(x, cury)] = '0';
    }
}

bool checkRow(int x, int nx) {
    bool ans = false;
    if (x > nx)
        swap(x, nx);
    // 每一行从x-2 ~ nx检查后面3格及以上是否相同
    for (int y = 0; y < maxy; ++y)
        for (int i = max(x - 2, 0); i <= min(nx, maxx - 3); ++i) {
            int ti = i;
            while (ti < maxx && newStatus[idx(ti, y)] != '0' && newStatus[idx(ti, y)] == newStatus[idx(ti + 1, y)])
                ++ti;
            if (ti - i >= 2) {
                ans = true;
                for (int j = i; j <= ti; ++j)
                    flag[j][y] = true;
            }
            i = ti;
        }
    return ans;
}

bool checkCol(int x) {
    bool ans = false;
    // 每一列从0 ~ maxy-3检查上面3格及以上是否相同
    for (int i = 0; i <= maxy - 3; ++i) {
        int ti = i;
        while (ti < maxy && newStatus[idx(x, ti)] != '0' && newStatus[idx(x, ti)] == newStatus[idx(x, ti + 1)])
            ++ti;
        if (ti - i >= 2) {
            ans = true;
            for (int j = i; j <= ti; ++j)
                flag[x][j] = true;
        }
        i = ti;
    }
    return ans;
}

void eraseBlock() {
    for (int x = 0; x < maxx; ++x)
        for (int y = 0; y < maxy; ++y)
            if (flag[x][y]) {
                newStatus[index] = '0';
                flag[x][y] = false;
            }
}

int ppp = 0;

void printBlock() {
    for (int y = maxy - 1; y >= 0; --y) {
        for (int x = 0; x < maxx; ++x)
            cout << newStatus[index] << " ";
        cout << endl;
    }
    cout << endl;
    ++ppp;
}

// 消除过就返回true，表示还要继续消除
bool checkAll(int x, int nx) {
    // 不断检查、移除、调整
    bool f1 = checkRow(x, nx), f2 = false, f3 = false;
    if (nx != maxx)
        f2 = checkCol(x), f3 = checkCol(nx);
    // 注意不能直接checkRow(x, nx) || checkCol(x) || checkCol(nx)，因为会短路
    if (f1 || f2 || f3) {
        eraseBlock();
        adjust();
        checkAll(0, maxx);
    }
}

void caculStatus(int x, int y, int direct) {
    newStatus = status;
    int nx = x + direct;
    swap(newStatus[index], newStatus[idx(nx, y)]);
    // 如果待交换的方块为空，则需要调整
    if (newStatus[idx(nx, y)] == '0')
        adjust();
    // 消除方块
    checkAll(x, nx);
}

void bfs() {
    queue<Node> q;
    q.push(Node(status));
    exist.insert(status);
    while (!q.empty()) {
        Node node = q.front();
        q.pop();
        status = node.status;
        vector<Step> step = node.step;
        // n步之内走不完
        if (step.size() == n)
            break;
        // string tmp = "10000002100000214000034000002334000";
        // if (status == tmp)
        //     int p = 1;
        // 按字典序检查每个方块
        for (int x = 0; x < maxx; ++x)
            for (int y = 0; y < maxy; ++y)
                // 右移优先于左移
                for (int i = 1; i >= -1; i -= 2)
                    if (valid(x, y, i)) {
                        caculStatus(x, y, i);
                        // n步之内走完了
                        if (newStatus == target) {
                            for (vector<Step>::iterator it = step.begin(); it != step.end(); ++it)
                                cout << it->x << " " << it->y << " " << it->direct << endl;
                            cout << x << " " << y << " " << i << endl;
                            return;
                        }
                        if (exist.count(newStatus) == 0) {
                            step.push_back(Step(x, y, i));
                            exist.insert(newStatus);
                            // cout << step.size() << endl;
                            // printBlock();
                            q.push(Node(newStatus, step));
                            step.pop_back();
                        }
                    }
    }
    cout << -1;
}

#define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> n;
    int tmp;
    for (int x = 0; x < maxx; ++x)
        for (int y = 0;; ++y) {
            cin >> tmp;
            if (tmp == 0) {
                for (; y < maxy; ++y)
                    status += '0';
                break;
            }
            status += toChar(tmp);
        }
    bfs();
    return 0;
}