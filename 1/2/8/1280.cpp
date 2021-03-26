#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;

struct Job {
    int start, last;
    Job() {}
};

const int maxn = 10005;
// dp[i]表示i...t时间内能获得的最大空暇时间
// 若i时刻没有任务，则dp[i] = dp[i+1] + 1
// 若i时刻有任务，则dp[i] = dp[i+t[i]]，注意可能有多个任务，取空暇时间最长的
int t, n, dp[maxn] = { 0 };
Job job[maxn];

bool cmp(Job& a, Job& b) { return a.start > b.start; }

int main() {
// #define DEBUG
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    cin >> t >> n;
    for (int i = 0; i < n; ++i)
        cin >> job[i].start >> job[i].last;
    sort(job, job + n, cmp);
    int cur = 0;
    for (int i = t; i > 0; --i)
        // 有任务
        if (cur < n && job[cur].start == i)
            while (cur < n && job[cur].start == i)
                dp[i] = max(dp[i], dp[i + job[cur++].last]);
        else
            dp[i] = dp[i + 1] + 1;
    cout << dp[1];
    return 0;
}