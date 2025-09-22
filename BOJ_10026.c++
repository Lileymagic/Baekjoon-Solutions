// 문제
// 적록색약은 빨간색과 초록색의 차이를 거의 느끼지 못한다. 
// 따라서, 적록색약인 사람이 보는 그림은 아닌 사람이 보는 그림과는 좀 다를 수 있다.

// 크기가 N×N인 그리드의 각 칸에 R(빨강), G(초록), B(파랑) 중 하나를 색칠한 그림이 있다. 
// 그림은 몇 개의 구역으로 나뉘어져 있는데, 구역은 같은 색으로 이루어져 있다.
//  또, 같은 색상이 상하좌우로 인접해 있는 경우에 두 글자는 같은 구역에 속한다. 
//  (색상의 차이를 거의 느끼지 못하는 경우도 같은 색상이라 한다)

// 예를 들어, 그림이 아래와 같은 경우에

// RRRBB
// GGBBB
// BBBRR
// BBRRR
// RRRRR
// 적록색약이 아닌 사람이 봤을 때 구역의 수는 총 4개이다. 
// (빨강 2, 파랑 1, 초록 1) 하지만, 적록색약인 사람은 구역을 3개 볼 수 있다. (빨강-초록 2, 파랑 1)

// 그림이 입력으로 주어졌을 때, 적록색약인 사람이 봤을 때와 아닌 사람이 봤을 때 구역의 수를 구하는 프로그램을 작성하시오.

// 입력
// 첫째 줄에 N이 주어진다. (1 ≤ N ≤ 100)

// 둘째 줄부터 N개 줄에는 그림이 주어진다.

// 출력
// 적록색약이 아닌 사람이 봤을 때의 구역의 개수와 적록색약인 사람이 봤을 때의 구역의 수를 공백으로 구분해 출력한다.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// 2차원 좌표
typedef struct coordinate{
    int x, y;

    // 생성자
    coordinate(): x(0), y(0) {}
    coordinate(int x, int y): x(x), y(y) {}
}coordinate;

void bfs(const vector<vector<char>>& draw, vector<vector<int>>& section, int count, int x, int y) {
    queue<coordinate> q;
    q.push(coordinate(x, y));
    section[y][x] = count;

    int v_size = draw.size();
    char color = draw[y][x];
    int nx[] = {1, -1, 0, 0};
    int ny[] = {0, 0, 1, -1};
    int size = 4;
    int dx, dy;

    coordinate coord;
    while (!q.empty()) {
        coord = q.front();
        q.pop();

        for(int i = 0; i < size; i++) {
            dx = coord.x + nx[i];
            dy = coord.y + ny[i];

            if (dx >= 0 && dx < v_size && dy >= 0 && dy < v_size && section[dy][dx] == 0 && draw[dy][dx] == color) {
                q.push(coordinate(dx, dy));
                section[dy][dx] = count;
            }
        }
    }
}

void bfs_blind(const vector<vector<char>>& draw, vector<vector<int>>& section, int count, int x, int y) {
    queue<coordinate> q;
    q.push(coordinate(x, y));
    section[y][x] = count;

    int v_size = draw.size();
    char color = draw[y][x];
    if (color == 'R') color = 'G';
    int nx[] = {1, -1, 0, 0};
    int ny[] = {0, 0, 1, -1};
    int size = 4;
    int dx, dy;
    char d_color;
    coordinate coord;
    while (!q.empty()) {
        coord = q.front();
        q.pop();

        for(int i = 0; i < size; i++) {
            dx = coord.x + nx[i];
            dy = coord.y + ny[i];
            if (dx >= 0 && dx < v_size && dy >= 0 && dy < v_size && section[dy][dx] == 0) {
                d_color = draw[dy][dx];
                if (d_color == 'R') d_color = 'G';

                if (color == d_color) {
                    q.push(coordinate(dx, dy));
                    section[dy][dx] = count;
                }
            }
        }
    }
}

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<vector<char>> draw(N, vector<char>(N));
    vector<vector<int>> section(N, vector<int>(N, 0));

    // 정보 입력
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            cin >> draw[y][x]; 
        }
    }

    // 정답 계산
    int count_bfs = 1;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (section[y][x] == 0) {
                bfs(draw, section, count_bfs, x, y);
                count_bfs++;
            }
        }
    }

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            section[y][x] = 0;
        }
    }

    int count_blind_bfs = 1;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (section[y][x] == 0) {
                bfs_blind(draw, section, count_blind_bfs, x, y);
                count_blind_bfs++;
            }
        }
    }

    cout << count_bfs - 1 << " " << count_blind_bfs - 1;

    return 0;
}