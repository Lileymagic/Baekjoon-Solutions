// 문제
// 그래프를 DFS로 탐색한 결과와 BFS로 탐색한 결과를 출력하는 프로그램을 작성하시오.
//  단, 방문할 수 있는 정점이 여러 개인 경우에는 정점 번호가 작은 것을 먼저 방문하고,
//   더 이상 방문할 수 있는 점이 없는 경우 종료한다. 정점 번호는 1번부터 N번까지이다.

// 입력
// 첫째 줄에 정점의 개수 N(1 ≤ N ≤ 1,000), 간선의 개수 M(1 ≤ M ≤ 10,000), 탐색을 시작할 정점의 번호 V가 주어진다. 
// 다음 M개의 줄에는 간선이 연결하는 두 정점의 번호가 주어진다.
//  어떤 두 정점 사이에 여러 개의 간선이 있을 수 있다. 입력으로 주어지는 간선은 양방향이다.

// 출력
// 첫째 줄에 DFS를 수행한 결과를, 그 다음 줄에는 BFS를 수행한 결과를 출력한다. V부터 방문된 점을 순서대로 출력하면 된다.


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class graph{
private:
    int numVertices;
    int isVisited[1001] = {};
    vector<vector<int>> adjList;
    queue<int> BFS_queue;

public:
    // 생성자
    graph(int n) : numVertices(n) {
        adjList.resize(n + 1);
    }

    // 간선 추가
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // 리스트를 오름차순으로 정렬
    void sortAdjList() {
        for (int i = 1; i <= numVertices; i++) {
            sort(adjList[i].begin(), adjList[i].end());
        }
    }

    // isVisited 배열 초기화
    void visitClear() {
        for (int i = 0; i < 1001; i++) {
            isVisited[i] = 0;
        }
    }

    // DFS 순회
    void DFS(int V) {
        isVisited[V] = 1;
        cout << V << " ";

        for(int i = 0; i < adjList[V].size(); i++) {
            // 인접한 노드에 아직 방문한 적이 없다면
            if (isVisited[adjList[V][i]] == 0) {
                DFS(adjList[V][i]);
            }
        }
    }

    // BFS 순회
    void BFS(int V) {
        BFS_queue.push(V);
        isVisited[V] = 1;
        cout << V << " ";

        int tmp;
        while (!BFS_queue.empty()) {
            tmp = BFS_queue.front();
            BFS_queue.pop();

            for(int i = 0; i < adjList[tmp].size(); i++) {
                // 인접한 노드에 아직 방문한 적이 없다면
                if (isVisited[adjList[tmp][i]] == 0) {
                    BFS_queue.push(adjList[tmp][i]);
                    isVisited[adjList[tmp][i]] = 1;
                    cout << adjList[tmp][i] << " ";
                }
            }
        }
    }
};

int main(void) {
    // 기본 설정
    int N, M, V;
    cin >> N >> M >> V;

    // 그래프에 간선 입력
    graph graph(N);
    int u, v;
    for (int i = 0; i< M; i++) {
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    // DFS, BFS 순회 결과 출력
    graph.visitClear(); graph.sortAdjList();
    graph.DFS(V);
    cout << endl; graph.visitClear();
    graph.BFS(V);

    return 0;
}