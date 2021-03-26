#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// #define DEBUG

const int maxn = 105;
const string target = "yizhong";
struct Coord {
    int x, y;
    Coord() {}
    Coord(int _x, int _y)
        : x(_x)
        , y(_y) {}
};
const Coord direct[8] = { { -1, 0 }, { -1, 1 }, { 0, 1 }, { 1, 1 }, { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, -1 } };
int n, tag[maxn][maxn] = { 0 };
string word[maxn];
vector<Coord> remain;

bool valid(int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < n)
        return true;
    return false;
}

void handle(int x, int y) {
    for (int i = 0; i < 8; ++i) {
        int nx = x, ny = y;
        remain.push_back(Coord(nx, ny));
        int j;
        for (j = 1; j < target.size(); ++j) {
            nx += direct[i].x;
            ny += direct[i].y;
            if (!valid(nx, ny) || word[nx][ny] != target[j])
                break;
            remain.push_back(Coord(nx, ny));
        }
        if (j == target.size())
            for (vector<Coord>::iterator it = remain.begin(); it != remain.end(); ++it)
                tag[it->x][it->y] = 1;
        else
            remain.clear();
    }
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> word[i];
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (word[i][j] == target[0])
                handle(i, j);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            if (tag[i][j])
                cout << word[i][j];
            else
                cout << "*";
        cout << endl;
    }
    return 0;
}