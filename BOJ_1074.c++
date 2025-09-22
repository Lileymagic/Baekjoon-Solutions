#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long long result = 0;

// 정답 계산
void calc(int size, int start_x, int start_y, int end_x, int end_y, long long cnt, int target_x, int target_y) {
    if (size != 1) {
        int half = pow(2, size - 1);
        long long token = half * half;
        if (target_x < start_x + half && target_y < start_y + half) 
            calc(size - 1, start_x, start_y, start_x + half, start_x + half, cnt, target_x, target_y);
        else if(target_x >= start_x + half && target_y < start_y + half) 
            calc(size - 1, start_x + half, start_y, end_x, start_y + half, cnt + token, target_x, target_y);
        else if(target_x < start_x + half && target_y >= start_y + half) 
            calc(size - 1, start_x, start_y + half, start_x + half, end_y, cnt + token * 2, target_x, target_y);
        else
            calc(size - 1, start_x + half, start_y + half, end_x, end_y, cnt + token * 3, target_x, target_y);
    } else {
        if (start_x == target_x && start_y == target_y) result = cnt;
        if (start_x + 1 == target_x && start_y == target_y) result = cnt + 1;
        if (start_x == target_x && start_y + 1 == target_y) result = cnt + 2;
        if (start_x + 1 == target_x && start_y + 1 == target_y) result = cnt + 3;
    }
}

int main(void) {
    int N, r, c;
    cin >> N >> r >> c;

    int size = pow(2, N);
    // vector<vector<int>> array(size, vector<int>(size));

    // 답 계산
    calc(N, 0, 0, size, size, 0, c, r);

    cout << result;
}