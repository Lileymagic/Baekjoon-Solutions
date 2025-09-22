// 창고에 보관되는 토마토들 중에는 잘 익은 것도 있지만, 아직 익지 않은 토마토들도 있을 수 있다. 
// 보관 후 하루가 지나면, 익은 토마토들의 인접한 곳에 있는 익지 않은 토마토들은 익은 토마토의 영향을 받아 익게 된다. 
// 하나의 토마토에 인접한 곳은 위, 아래, 왼쪽, 오른쪽, 앞, 뒤 여섯 방향에 있는 토마토를 의미한다. 
// 대각선 방향에 있는 토마토들에게는 영향을 주지 못하며, 토마토가 혼자 저절로 익는 경우는 없다고 가정한다. 
// 철수는 창고에 보관된 토마토들이 며칠이 지나면 다 익게 되는지 그 최소 일수를 알고 싶어 한다.

// 토마토를 창고에 보관하는 격자모양의 상자들의 크기와 익은 토마토들과 익지 않은 토마토들의 정보가 주어졌을 때, 
// 며칠이 지나면 토마토들이 모두 익는지, 그 최소 일수를 구하는 프로그램을 작성하라. 
// 단, 상자의 일부 칸에는 토마토가 들어있지 않을 수도 있다.

// 입력
// 첫 줄에는 상자의 크기를 나타내는 두 정수 M,N과 쌓아올려지는 상자의 수를 나타내는 H가 주어진다. 
// M은 상자의 가로 칸의 수, N은 상자의 세로 칸의 수를 나타낸다. 단, 2 ≤ M ≤ 100, 2 ≤ N ≤ 100, 1 ≤ H ≤ 100 이다.
//  둘째 줄부터는 가장 밑의 상자부터 가장 위의 상자까지에 저장된 토마토들의 정보가 주어진다. 
//  즉, 둘째 줄부터 N개의 줄에는 하나의 상자에 담긴 토마토의 정보가 주어진다. 
//  각 줄에는 상자 가로줄에 들어있는 토마토들의 상태가 M개의 정수로 주어진다. 
//  정수 1은 익은 토마토, 정수 0 은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다. 
//  이러한 N개의 줄이 H번 반복하여 주어진다.

// 토마토가 하나 이상 있는 경우만 입력으로 주어진다.

// 출력
// 여러분은 토마토가 모두 익을 때까지 최소 며칠이 걸리는지를 계산해서 출력해야 한다. 
// 만약, 저장될 때부터 모든 토마토가 익어있는 상태이면 0을 출력해야 하고, 토마토가 모두 익지는 못하는 상황이면 -1을 출력해야 한다.

#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

// 3차원 좌표를 나타내는 구조체
typedef struct coordinate {
int x, y, z;

// 생성자
coordinate(): x(0), y(0), z(0) {}
coordinate(int x, int y, int z): x(x), y(y), z(z) {}

}coordinate;

void bfs(const vector<vector<vector<int>>>& box, vector<vector<vector<int>>>& day, vector<vector<vector<int>>>& visited) {
    queue<coordinate> q;

    int x_size = box[0][0].size();
    int y_size = box[0].size();
    int z_size = box.size();

    coordinate coord;

    int nx[] = {1, -1, 0, 0, 0, 0};
    int ny[] = {0, 0, 1, -1, 0, 0};
    int nz[] = {0, 0, 0, 0, 1, -1};
    int size = 6;

    int dx, dy, dz;
    int count;

    for (int i = 0; i < z_size; i++) {
        for (int j = 0; j < y_size; j++) {
            for (int k = 0; k < x_size; k++) {
                if (box[i][j][k] == 1) q.push(coordinate(k, j, i));
            }
        }
    }

    while (!q.empty()) {
        coord = q.front();
        q.pop();
        count = day[coord.z][coord.y][coord.x];

        for(int i = 0; i < size; i++) {
            dx = coord.x + nx[i];
            dy = coord.y + ny[i];
            dz = coord.z + nz[i];

            if (dx >= 0 && dx < x_size && dy >= 0 && dy < y_size && dz >= 0 && dz < z_size && visited[dz][dy][dx] != 1 && box[dz][dy][dx] != -1) {
                visited[dz][dy][dx] = 1;
                q.push(coordinate(dx, dy, dz));

                if (day[dz][dy][dx] == -1) day[dz][dy][dx] = count + 1;
                else day[dz][dy][dx] = min(day[dz][dy][dx], count + 1);
            }// if
        }// for
    }// while
}// bfs

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, N, H;

    cin >> M >> N >> H;

    // box[z][y][x] 
    vector<vector<vector<int>>> box(H, vector<vector<int>>(N, vector<int>(M)));
    vector<vector<vector<int>>> day(H, vector<vector<int>>(N, vector<int>(M, -1)));
    vector<vector<vector<int>>> visited(H, vector<vector<int>>(N, vector<int>(M, 0)));

    // 정보 입력
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                cin >> box[i][j][k];
                if(box[i][j][k] == 1) day[i][j][k] = 0;
                else if(box[i][j][k] == 0) day[i][j][k] = -1;
            }
        }
    }

    // 정답 계산
    bfs(box, day, visited);

    int result = 0;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < M; k++) {
                if (box[i][j][k] == -1) continue;

                if (day[i][j][k] == -1) {
                    cout << -1;
                    return 0;
                }

                result = max(result, day[i][j][k]);
            }
        }
    }

    cout << result;

    return 0;
}