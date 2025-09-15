// 문제
// 가중치 없는 방향 그래프 G가 주어졌을 때, 모든 정점 (i, j)에 대해서, 
// i에서 j로 가는 길이가 양수인 경로가 있는지 없는지 구하는 프로그램을 작성하시오.

// 입력
// 첫째 줄에 정점의 개수 N (1 ≤ N ≤ 100)이 주어진다. 둘째 줄부터 N개 줄에는 그래프의 인접 행렬이 주어진다. 
// i번째 줄의 j번째 숫자가 1인 경우에는 i에서 j로 가는 간선이 존재한다는 뜻이고, 0인 경우는 없다는 뜻이다. 
// i번째 줄의 i번째 숫자는 항상 0이다.

// 출력
// 총 N개의 줄에 걸쳐서 문제의 정답을 인접행렬 형식으로 출력한다. 
// 정점 i에서 j로 가는 길이가 양수인 경로가 있으면 i번째 줄의 j번째 숫자를 1로, 없으면 0으로 출력해야 한다.

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

//dfs 순회
void dfs(const vector<vector<int>>& graph, vector<int>& visited, int vertex) {
    for (int i = 0; i < visited.size(); i++) {
        if (visited[i] == 0 && graph[vertex][i] == 1) {
            visited[i] = 1;
            dfs(graph, visited, i); 
        }
    }
}

int main(void) {
    // 기본 설정 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    // 그래프 정보 입력
    vector<vector<int>> graph(N, vector<int>(N, 0));
    vector<int> visited(N, 0);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> graph[i][j];
        }
    }

    // dfs로 순회하며 정답 출력
    for(int i = 0; i < N; i++) {
        fill(visited.begin(), visited.end(), 0);
        dfs(graph, visited, i);

        for(int i = 0; i < N; i++) {
            if (visited[i] == 0) cout << "0 ";
            else cout << "1 ";
        }
        cout << "\n";
    }
    return 0;
}