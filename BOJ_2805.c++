#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, height;
    long long M;
    vector<long long> trees;
    cin >> N >> M;

    // 나무 높이 입력
    for (int i = 0; i < N; i++) {
        cin >> height;
        trees.push_back(height);
    }

    // 벡터 정렬하기 (내림차순)
    sort(trees.begin(), trees.end(), greater<long long>());

    // 결과 계산하기
    long long cur_height = trees[0];
    long long cur_length = 0;
    long long stack = 0;

    for (int i = 0; i < (int)trees.size(); i++) {
        stack = i + 1;

        // 마지막 나무까지 온 경우
        if (i == (int)trees.size() - 1) {
            cur_height = trees[i];
            long long need = M - cur_length;
            long long steps = (need + stack - 1) / stack;
            cur_height -= steps;
            if (cur_height < 0) cur_height = 0;
            cout << cur_height;
            return 0;
        }

        long long diff = trees[i] - trees[i + 1];

        // 이번 구간에서 필요한 길이를 다 채울 수 있을 경우
        if (cur_length + diff * stack >= M) {
            cur_height = trees[i];
            long long need = M - cur_length;
            long long steps = (need + stack - 1) / stack;
            cur_height -= steps;
            if (cur_height < 0) cur_height = 0;
            cout << cur_height << endl;
            return 0;
        }

        // 아직 모자라면 현재 구간 통째로 잘라내기
        cur_length += diff * stack;
    }
}
