#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
// #define DEBUG

const int maxn = 1e5;
int n, r, q;
struct Player {
    int id, score, strength;
    Player() {}
    bool operator<(const Player& a) const {
        if (score != a.score)
            return score > a.score;
        return id < a.id;
    }
};
Player player[maxn * 2], winner[maxn], loser[maxn];

void mergePlayer() {
    int p1 = 0, p2 = 0, p = 0;
    while (p1 < n && p2 < n) {
        if (winner[p1] < loser[p2])
            player[p++] = winner[p1++];
        else
            player[p++] = loser[p2++];
    }
    while (p1 < n)
        player[p++] = winner[p1++];
    while (p2 < n)
        player[p++] = loser[p2++];
}

int main() {
#ifdef DEBUG
    freopen("d:\\input.txt", "r", stdin);
    freopen("d:\\output.txt", "w", stdout);
#endif
    cin >> n >> r >> q;
    for (int i = 0; i < n * 2; ++i) {
        cin >> player[i].score;
        player[i].id = i + 1;
    }
    for (int i = 0; i < n * 2; ++i)
        cin >> player[i].strength;
    sort(player, player + 2 * n);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < n; ++j) {
            if (player[2 * j].strength > player[2 * j + 1].strength) {
                player[2 * j].score++;
                winner[j] = player[2 * j];
                loser[j] = player[2 * j + 1];
            } else {
                player[2 * j + 1].score++;
                winner[j] = player[2 * j + 1];
                loser[j] = player[2 * j];
            }
        }
        mergePlayer();
    }
    cout << player[q - 1].id;
    return 0;
}