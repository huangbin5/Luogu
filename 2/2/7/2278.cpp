#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;

struct Node {
    int id, arrive, process, priority;
    Node(int _id, int _arrive, int _process, int _priority) : id(_id), arrive(_arrive), process(_process), priority(_priority) {}
    bool operator<(const Node& a) const {
        if (priority != a.priority)
            return priority < a.priority;
        return arrive > a.arrive;
    }
};

priority_queue<Node> pq;

// #define DEBUG
int main() {
#ifdef DEBUG
    freopen("d:\\.in", "r", stdin);
    freopen("d:\\.out", "w", stdout);
#endif
    int id, arrive, process, priority, startTime = -1;
    while (scanf("%d%d%d%d", &id, &arrive, &process, &priority) != EOF) {
        // 在两个任务到达的间隔期内不断地取出任务执行
        while (!pq.empty()) {
            Node curNode = pq.top();
            pq.pop();
            startTime = max(startTime, curNode.arrive);
            if (startTime + curNode.process <= arrive) {
                // 能执行完
                startTime += curNode.process;
                printf("%d %d\n", curNode.id, startTime);
            } else {
                // 不能执行完就放回去
                curNode.process -= arrive - startTime;
                pq.push(curNode);
                startTime = arrive;
                break;
            }
        }
        pq.push(Node(id, arrive, process, priority));
    }
    // 所有任务都入队了，处理剩余任务
    startTime = max(startTime, pq.top().arrive);
    while (!pq.empty()) {
        Node curNode = pq.top();
        pq.pop();
        // 一定要执行完
        startTime += curNode.process;
        printf("%d %d\n", curNode.id, startTime);
    }
    return 0;
}