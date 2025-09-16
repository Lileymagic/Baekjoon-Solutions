// 문제
// 지도가 주어지면 모든 지점에 대해서 목표지점까지의 거리를 구하여라.

// 문제를 쉽게 만들기 위해 오직 가로와 세로로만 움직일 수 있다고 하자.

// 입력
// 지도의 크기 n과 m이 주어진다. n은 세로의 크기, m은 가로의 크기다.(2 ≤ n ≤ 1000, 2 ≤ m ≤ 1000)

// 다음 n개의 줄에 m개의 숫자가 주어진다. 
// 0은 갈 수 없는 땅이고 1은 갈 수 있는 땅, 2는 목표지점이다. 입력에서 2는 단 한개이다.

// 출력
// 각 지점에서 목표지점까지의 거리를 출력한다. 
// 원래 갈 수 없는 땅인 위치는 0을 출력하고, 원래 갈 수 있는 땅인 부분 중에서 도달할 수 없는 위치는 -1을 출력한다.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 2차원 좌표를 나타내는 구조체
typedef struct coordinate {
    int x;
    int y;
    
    // 생성자
    coordinate(int x, int y): x(x), y(y) {};
}coordinate;

// 변형된 bfs
void bfs (const vector<vector<int>>& graph, vector<vector<int>>& distance, int target_x, int target_y) {
    queue<coordinate> bfs_queue;
    bfs_queue.push(coordinate(target_x, target_y));
    int cur_distance = 0;
    
    int cur_x, cur_y;
    int nx[] = {-1, 1, 0, 0};
    int ny[] = {0, 0, -1, 1};
    int dx, dy;
    int size = 4;

    while (bfs_queue.empty() != 1) {
        coordinate cur_coord = bfs_queue.front();
        bfs_queue.pop();

        cur_x = cur_coord.x;
        cur_y = cur_coord.y;

        // 문제에 제시된 조건에 따라 bfs 탐색 진행하기
        for(int i = 0; i < size; i++) {
            dx = nx[i] + cur_x;
            dy = ny[i] + cur_y;

            if (dx >= 0 && dx < graph[0].size() && dy >= 0 && dy < graph.size() && distance[dy][dx] == 0 && graph[dy][dx] != 2 && graph[dy][dx] != 0) {
                bfs_queue.push(coordinate(dx, dy));
                distance[dy][dx] = distance[cur_y][cur_x] + 1;
            }
        }
    }


}

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> graph(n, vector<int>(m));
    vector<vector<int>> distance(n, vector<int>(m, 0));

    // 그래프 정보 입력
    int num;
    int target_x, target_y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> num;

            // 2라면 타겟 노드로 지정
            if(num == 2) {
                target_x = j;
                target_y = i;
            }
            graph[i][j] = num;
        }
    }

    // bfs 진행 후 vector 순회하며 거리 나열
    bfs(graph, distance, target_x, target_y);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (distance[i][j] == 0) {
                if (graph[i][j] == 2 || graph[i][j] == 0) cout << 0 << " ";
                else cout << -1 << " ";
            } else cout << distance[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}