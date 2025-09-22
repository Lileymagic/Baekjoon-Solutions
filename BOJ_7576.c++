// 창고에 보관되는 토마토들 중에는 잘 익은 것도 있지만, 아직 익지 않은 토마토들도 있을 수 있다. 
// 보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받아 익게 된다. 
// 하나의 토마토의 인접한 곳은 왼쪽, 오른쪽, 앞, 뒤 네 방향에 있는 토마토를 의미한다. 
// 대각선 방향에 있는 토마토들에게는 영향을 주지 못하며, 토마토가 혼자 저절로 익는 경우는 없다고 가정한다. 
// 철수는 창고에 보관된 토마토들이 며칠이 지나면 다 익게 되는지, 그 최소 일수를 알고 싶어 한다.

// 토마토를 창고에 보관하는 격자모양의 상자들의 크기와 익은 토마토들과 익지 않은 토마토들의 정보가 주어졌을 때, 
// 며칠이 지나면 토마토들이 모두 익는지, 그 최소 일수를 구하는 프로그램을 작성하라. 
// 단, 상자의 일부 칸에는 토마토가 들어있지 않을 수도 있다.

// 입력
// 첫 줄에는 상자의 크기를 나타내는 두 정수 M,N이 주어진다. M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다. 
// 단, 2 ≤ M,N ≤ 1,000 이다. 둘째 줄부터는 하나의 상자에 저장된 토마토들의 정보가 주어진다. 
// 즉, 둘째 줄부터 N개의 줄에는 상자에 담긴 토마토의 정보가 주어진다. 
// 하나의 줄에는 상자 가로줄에 들어있는 토마토의 상태가 M개의 정수로 주어진다. 
// 정수 1은 익은 토마토, 정수 0은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다.

// 토마토가 하나 이상 있는 경우만 입력으로 주어진다.

// 출력
// 여러분은 토마토가 모두 익을 때까지의 최소 날짜를 출력해야 한다. 
// 만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 
// 토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 2차원 좌표를 표현하는 구조체
typedef struct coordinate {
    int x, y;

    // 생성자
    coordinate(): x(0), y(0) {}
    coordinate(int x, int y): x(x), y(y) {}
}coordinate;

// 변형된 형태의 bfs
void bfs(const vector<vector<int>>& box, vector<vector<int>>& day) {
    queue<coordinate> q;

    // 벡터를 순회하며 익은 토마토를 모두 큐에 삽입
    int x_size = box[0].size();
    int y_size = box.size();

    for (int y = 0; y < y_size; y++) {
        for (int x = 0; x < x_size; x++) {
            if(box[y][x] == 1) q.push(coordinate(x ,y));
        }
    }

    // 접근의 규칙 작성
    int nx[] = {1, -1, 0, 0};
    int ny[] = {0, 0, 1, -1};
    int size = 4;
    int dx, dy;
    
    // bfs 실행
    coordinate coord;
    while(!q.empty()) {
        coord = q.front();
        q.pop();

        // 조건에 따라 접근
        for (int i = 0; i < size; i++) {
            dx = coord.x + nx[i];
            dy = coord.y + ny[i];

            if (dx >= 0 && dx < x_size && dy >= 0 && dy < y_size && box[dy][dx] != -1 && day[dy][dx] == -1) {
                q.push(coordinate(dx, dy));
                day[dy][dx] = day[coord.y][coord.x] + 1;
            }
        } // for
    } // while
} // bfs

int main(void){
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int M, N;
    cin >> M >> N;

    vector<vector<int>> box(N, vector<int>(M));
    vector<vector<int>> day(N, vector<int>(M, -1));

    // 정보 입력
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            cin >> box[y][x];
            if(box[y][x] == 1) day[y][x] = 0; 
        }
    }

    // bfs 진행
    bfs(box, day);

    // 벡터를 순회하며 정답 계산
    int result = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < M; x++) {
            if (box[y][x] == -1) continue;
            
            if (day[y][x] == -1) {
                cout << -1;
                return 0;
            } else {
                result = max(result, day[y][x]);
            }
        }
    }

    cout << result;

    return 0;
}