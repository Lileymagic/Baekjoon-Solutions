// 문제
// N×M크기의 배열로 표현되는 미로가 있다.

// 1	0	1	1	1	1
// 1	0	1	0	1	0
// 1	0	1	0	1	1
// 1	1	1	0	1	1
// 미로에서 1은 이동할 수 있는 칸을 나타내고, 0은 이동할 수 없는 칸을 나타낸다. 이러한 미로가 주어졌을 때, 
// (1, 1)에서 출발하여 (N, M)의 위치로 이동할 때 지나야 하는 최소의 칸 수를 구하는 프로그램을 작성하시오. 
// 한 칸에서 다른 칸으로 이동할 때, 서로 인접한 칸으로만 이동할 수 있다.

// 위의 예에서는 15칸을 지나야 (N, M)의 위치로 이동할 수 있다. 칸을 셀 때에는 시작 위치와 도착 위치도 포함한다.

// 입력
// 첫째 줄에 두 정수 N, M(2 ≤ N, M ≤ 100)이 주어진다. 다음 N개의 줄에는 M개의 정수로 미로가 주어진다. 각각의 수들은 붙어서 입력으로 주어진다.

// 출력
// 첫째 줄에 지나야 하는 최소의 칸 수를 출력한다. 항상 도착위치로 이동할 수 있는 경우만 입력으로 주어진다.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

// 2차원 좌표를 나타내는 구조체
class coordinate{
public:
    int x;
    int y;

    // 생성자
    coordinate(int x, int y): x(x), y(y) {};
};

// 변형된 BFS 순회
void BFS (const vector<vector<int>>& graph, vector<vector<int>>& visited) {
    visited[1][1] = 1;
    queue<coordinate> q;
    q.push(coordinate(1, 1));

    int cur_x, cur_y;
    coordinate cur_coord(0, 0);

    while (!q.empty()) {
        cur_coord = q.front();
        q.pop();
        cur_x = cur_coord.x; cur_y = cur_coord.y;

        // 조건에 따라 상하좌우 탐색
        // 하
        if (cur_y != graph.size() - 1 && graph[cur_y + 1][cur_x] == 1 && visited[cur_y + 1][cur_x] == 0) { 
            q.push(coordinate(cur_x, cur_y + 1));
            visited[cur_y + 1][cur_x] = visited[cur_y][cur_x] + 1;
        }
        // 우
        if (cur_x != graph[1].size() - 1 && graph[cur_y][cur_x + 1] == 1 && visited[cur_y][cur_x + 1] == 0) { 
            q.push(coordinate(cur_x + 1, cur_y));
            visited[cur_y][cur_x + 1] = visited[cur_y][cur_x] + 1;
        }
        // 상
        if (cur_y != 1 && graph[cur_y - 1][cur_x] == 1 && visited[cur_y - 1][cur_x] == 0) { 
            q.push(coordinate(cur_x, cur_y - 1));
            visited[cur_y - 1][cur_x] = visited[cur_y][cur_x] + 1;
        }
        // 좌
        if (cur_x != 1 && graph[cur_y][cur_x - 1] == 1 && visited[cur_y][cur_x - 1] == 0) { 
            q.push(coordinate(cur_x - 1, cur_y));
            visited[cur_y][cur_x - 1] = visited[cur_y][cur_x] + 1;
        }
    }
}

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;
    
    vector<vector<int>> graph(N + 1, vector<int>(M + 1));
    vector<vector<int>> visited(N + 1, vector<int>(M + 1, 0));
    string number_str;
    int number;

    // 정보 입력
    for (int i = 1; i <= N; i++) {
        cin >> number_str;
        for (int j = 1; j <= M; j++) {
            number = number_str[j - 1] -'0';

            graph[i][j] = number;
        }
    }

    // 정답 출력
    BFS(graph, visited);
    cout << visited[N][M];

    return 0;
}