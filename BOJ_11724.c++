// 문제
// 방향 없는 그래프가 주어졌을 때, 연결 요소 (Connected Component)의 개수를 구하는 프로그램을 작성하시오.

// 입력
// 첫째 줄에 정점의 개수 N과 간선의 개수 M이 주어진다. 
// (1 ≤ N ≤ 1,000, 0 ≤ M ≤ N×(N-1)/2) 둘째 줄부터 M개의 줄에 간선의 양 끝점 u와 v가 주어진다. (1 ≤ u, v ≤ N, u ≠ v) 같은 간선은 한 번만 주어진다.

// 출력
// 첫째 줄에 연결 요소의 개수를 출력한다.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 그래프 클래스
class graph {
private:
vector<vector<int>> adj_list;
vector<int> visited;

    // DFS 탐색
    void DFS(int vertex) {
        visited[vertex] = 1;

        for(int i = 0; i < adj_list[vertex].size(); i++) {
            if (visited[adj_list[vertex][i]] == 0) {
                DFS(adj_list[vertex][i]);
            }
        }
    }

public:
    // 생성자
    graph (int size) {
        adj_list.resize(size + 1);
        visited.resize(size + 1);
    }

    // 간선 추가하기
    void add_edge(int u, int v) {
        adj_list[u].push_back(v);

        // 양방향 그래프
        adj_list[v].push_back(u);
    }

    // 연결 요소의 수 구하기
    int calc_connected_component() {
        int cnt = 0;

        // visited 초기화
        fill(visited.begin(), visited.end(), 0);

        // 그래프 순회하며 연결 요소 체크하기
        for(int i = 1; i < visited.size(); i++) {
            if(visited[i] == 0) {
                cnt++; 
                DFS(i);
            }
        }
        // 연결 요소의 수 반환
        return cnt;
    }
};

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    // 간선 입력
    graph graph(N);
    int u, v;
    for (int i = 0; i < M; i++) {
        cin >> u >> v;
        graph.add_edge(u, v);
    }

    // 연결 요소의 수 계산
    cout << graph.calc_connected_component();

    return 0;
}