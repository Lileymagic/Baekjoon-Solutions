// 문제
// <그림 1>과 같이 정사각형 모양의 지도가 있다. 1은 집이 있는 곳을, 0은 집이 없는 곳을 나타낸다. 
// 철수는 이 지도를 가지고 연결된 집의 모임인 단지를 정의하고, 단지에 번호를 붙이려 한다. 
// 여기서 연결되었다는 것은 어떤 집이 좌우, 혹은 아래위로 다른 집이 있는 경우를 말한다. 
// 대각선상에 집이 있는 경우는 연결된 것이 아니다. <그림 2>는 <그림 1>을 단지별로 번호를 붙인 것이다. 
// 지도를 입력하여 단지수를 출력하고, 각 단지에 속하는 집의 수를 오름차순으로 정렬하여 출력하는 프로그램을 작성하시오.



// 입력
// 첫 번째 줄에는 지도의 크기 N(정사각형이므로 가로와 세로의 크기는 같으며 5≤N≤25)이 입력되고, 그 다음 N줄에는 각각 N개의 자료(0혹은 1)가 입력된다.

// 출력
// 첫 번째 줄에는 총 단지수를 출력하시오. 그리고 각 단지내 집의 수를 오름차순으로 정렬하여 한 줄에 하나씩 출력하시오.

#include <iostream>
#include <vector>
#include <algorithm>
#include <string> 

using namespace std;

// 변형된 형태의 DFS
void DFS(const vector<vector<int>>& graph, vector<vector<int>>& visited, int cur_x, int cur_y, int count) {
    visited[cur_y][cur_x] = count;
 
    int nx[] = {0, 0, -1, 1};
    int ny[] = {-1, 1, 0, 0};
    int size = 4;

    // 조건에 따라 상하좌우 탐색
    int dx, dy;
    for (int i = 0; i < size; i++) {
        dx = nx[i] + cur_x;
        dy = ny[i] + cur_y;

        if (dx >= 0 && dy >= 0 && dx < visited.size() && dy < visited.size() && visited[dy][dx] == 0 && graph[dy][dx] != 0) {
            DFS(graph, visited, dx, dy, count);
        }
    }
}

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<vector<int>> graph(N, vector<int>(N));
    vector<vector<int>> visited(N, vector<int>(N, 0));

    // 정보 입력
    string str;
    int number;
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (int j = 0; j < N; j++) {
            number = str[j] - '0';  // 숫자로 변환해서 입력
            graph[i][j] = number;
        }
    } 

    // DFS로 연결요소 시각화
    int cnt = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(visited[i][j] == 0 && graph[i][j] != 0) {
                DFS(graph, visited, j, i, cnt);
                cnt++;
            }
        }
    }

    // 각 부분의 크기 계산
    vector<int> int_vec;
    int size;

    for (int i = 1; i < cnt; i++) {
        size = 0;
        for (const auto& row: visited) {
            size += count(row.begin(), row.end(), i);
        }
        int_vec.push_back(size);
    }

    // 오름차순으로 크기 정렬 후 출력
    sort(int_vec.begin(), int_vec.end());

    cout << int_vec.size() << '\n';
    for (int i : int_vec) {
        cout << i << "\n";
    }

    return 0;
}