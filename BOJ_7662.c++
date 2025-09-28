#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

struct Node {
    long long int val;
    int id;
    bool operator<(const Node &o) const {
        return val < o.val;
    }
 };
 struct NodeMin {
    bool operator()(const Node &a, const Node &b) const {
        return a.val > b.val;
    }
 };

 int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;

     while (T--) {
        int k; cin >> k;
        priority_queue<Node> maxQ;
        priority_queue<Node, vector<Node>, NodeMin> minQ;
        vector<bool> visited(k, false); // 각 연산마다 id 부여
        int id = 0;

        for (int i = 0; i < k; i++) {
            char cmd; long long int n;
            cin >> cmd >> n;
            if (cmd == 'I') {
                maxQ.push({n, id});
                minQ.push({n, id});
                visited[id] = true;
                id++;
            } else if (cmd == 'D') {
                if (n == 1) { // 최댓값 삭제
                    while (!maxQ.empty() && !visited[maxQ.top().id]) maxQ.pop();
                    if (!maxQ.empty()) {
                        visited[maxQ.top().id] = false;
                        maxQ.pop();
                    }
                } else { // 최솟값 삭제
                    while (!minQ.empty() && !visited[minQ.top().id]) minQ.pop();
                    if (!minQ.empty()) {
                        visited[minQ.top().id] = false;
                        minQ.pop();
                    }
                }
            }
        }

        // 마지막 정리
        while (!maxQ.empty() && !visited[maxQ.top().id]) maxQ.pop();
        while (!minQ.empty() && !visited[minQ.top().id]) minQ.pop();

        if (maxQ.empty() || minQ.empty()) {
            cout << "EMPTY\n";
        } else {
            cout << maxQ.top().val << " " << minQ.top().val << "\n";
        }
     }

     return 0;
 }