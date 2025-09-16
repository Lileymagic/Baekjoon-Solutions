#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// 정답 계산
void calc(vector<vector<int>>& array, int size, int start, int end) {
    // size가 1이 아닐 때, 재귀 호출
    if (size != 1) {
        int token = pow(2, size - 1);
        
        for (int i = start; i <= end; i += token) {
            calc(array, size - 1, i, i + token);
        }   
    }
}

int main(void) {
    int N, r, c;
    cin >> N >> r >> c;

    int size = pow(2, N);
    vector<vector<int>> array(size, vector<int>(size));
}