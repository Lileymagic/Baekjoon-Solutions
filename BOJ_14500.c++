// 폴리오미노란 크기가 1×1인 정사각형을 여러 개 이어서 붙인 도형이며, 다음과 같은 조건을 만족해야 한다.

// 정사각형은 서로 겹치면 안 된다.
// 도형은 모두 연결되어 있어야 한다.
// 정사각형의 변끼리 연결되어 있어야 한다. 즉, 꼭짓점과 꼭짓점만 맞닿아 있으면 안 된다.
// 정사각형 4개를 이어 붙인 폴리오미노는 테트로미노라고 하며, 다음과 같은 5가지가 있다.



// 아름이는 크기가 N×M인 종이 위에 테트로미노 하나를 놓으려고 한다. 종이는 1×1 크기의 칸으로 나누어져 있으며, 각각의 칸에는 정수가 하나 쓰여 있다.

// 테트로미노 하나를 적절히 놓아서 테트로미노가 놓인 칸에 쓰여 있는 수들의 합을 최대로 하는 프로그램을 작성하시오.

// 테트로미노는 반드시 한 정사각형이 정확히 하나의 칸을 포함하도록 놓아야 하며, 회전이나 대칭을 시켜도 된다.

// 입력
// 첫째 줄에 종이의 세로 크기 N과 가로 크기 M이 주어진다. (4 ≤ N, M ≤ 500)

// 둘째 줄부터 N개의 줄에 종이에 쓰여 있는 수가 주어진다. i번째 줄의 j번째 수는 위에서부터 i번째 칸, 
// 왼쪽에서부터 j번째 칸에 쓰여 있는 수이다. 입력으로 주어지는 수는 1,000을 넘지 않는 자연수이다.

// 출력
// 첫째 줄에 테트로미노가 놓인 칸에 쓰인 수들의 합의 최댓값을 출력한다.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int calc_max(const vector<vector<int>> &arr) {
    int biggest = 0;

    int size_y = arr.size();
    int size_x = arr[0].size();
    int sum;

    // case 1
    int nx[] = {1, 1, 1, 0, -1, -1, -1};
    int ny[] = {0, 1, 2, 3, 2, 1, 0};
    int size_n = 7; int dy, dx;

    for (int y = 0; y < size_y - 2; y++) {
        for (int x = 0; x < size_x; x++) {
            sum = arr[y][x] + arr[y + 1][x] + arr[y + 2][x];
            for (int i = 0; i < size_n; i++) {
                dy = y + ny[i]; 
                dx = x + nx[i];

                if (dy >= 0 && dy < size_y && dx >= 0 && dx < size_x)
                    biggest = max(biggest, sum + arr[dy][dx]);
            }
        }
    }

    // case 2
    int nx2[] = {0, 1, 2, 3, 2, 1, 0};
    int ny2[] = {-1, -1, -1, 0, 1, 1, 1};
    size_n = 7;

    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x - 2; x++) {
            sum = arr[y][x] + arr[y][x + 1] + arr[y][x + 2];
            for (int i = 0; i < size_n; i++) {
                dy = y + ny2[i]; 
                dx = x + nx2[i];

                if (dy >= 0 && dy < size_y && dx >= 0 && dx < size_x)
                    biggest = max(biggest, sum + arr[dy][dx]);
            }
        }
    }

    //case 3
    int nx3[] = {0, 1, 1};
    int nx3_2[] = {1, 2, 2};
    int ny3[] = {-1, -1, 1};
    size_n = 3; int dx_2, dy_2;

    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x - 1; x++) {
            sum = arr[y][x] + arr[y][x + 1];
            for (int i = 0; i < size_n; i++) {
                dy = y + ny3[i];
                dx = x + nx3[i]; dx_2 = x + nx3_2[i];
        
                if (dy >= 0 && dy < size_y && dx >= 0 && dx < size_x && dx_2 >= 0 && dx_2 < size_x)
                    biggest = max(biggest, sum + arr[dy][dx] + arr[dy][dx_2]);
            }
        }
    }

    //case 4
    int nx4[] = {1, -1};
    int ny4[] = {0, 0};
    int ny4_2[] = {-1, -1};
    size_n = 2;

    for (int y = 0; y < size_y - 1; y++) {
        for (int x = 0; x < size_x; x++) {
            sum = arr[y][x] + arr[y + 1][x];
            for (int i = 0; i < size_n; i++) {
                dy = y + ny4[i]; dy_2 = y + ny4_2[i];
                dx = x + nx4[i]; 
        
                if (dy >= 0 && dy < size_y && dx >= 0 && dx < size_x && dy_2 >= 0 && dy_2 < size_y)
                    biggest = max(biggest, sum + arr[dy][dx] + arr[dy_2][dx]);
            }
        }
    }

    return biggest;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; int M;
    cin >> N >> M;

    vector<vector<int>> arr(N, vector<int>(M));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
        }
    }

    cout << calc_max(arr);

    return 0;
}