// 문제
// 2020년에 입학한 헌내기 도연이가 있다. 
// 도연이는 비대면 수업 때문에 학교에 가지 못해 학교에 아는 친구가 없었다. 
// 드디어 대면 수업을 하게 된 도연이는 어서 캠퍼스 내의 사람들과 친해지고 싶다. 

// 도연이가 다니는 대학의 캠퍼스에서 이동하는 방법은 벽이 아닌 상하좌우로 이동하는 것이다.
// 불쌍한 도연이를 위하여 캠퍼스에서 도연이가 만날 수 있는 사람의 수를 출력하는 프로그램을 작성해보자.

// 입력
// 첫째 줄에는 캠퍼스의 크기를 나타내는 두 정수가 주어진다

// 둘째 줄부터 N개의 줄에는 캠퍼스의 정보들이 주어진다. 
// O는 빈 공간, X는 벽, I는 도연이, P는 사람이다. I가 한 번만 주어짐이 보장된다.

// 출력
// 첫째 줄에 도연이가 만날 수 있는 사람의 수를 출력한다. 단, 아무도 만나지 못한 경우 TT를 출력한다.

#include <iostream>
#include <vector>

using namespace std;

// DFS 탐색 기반으로 커스텀 함수 구현
void search_campus(vector<vector<char>>const& campus, vector<vector<int>>& visited, int pos_N, int pos_M) {
    visited[pos_N][pos_M] = 1;
    
    // 벽이 아닐때만 상하좌우로 탐색 진행
    // 순서대로 상, 하, 좌, 우
    if (pos_N != 0 && campus[pos_N - 1][pos_M] != 'X' && visited[pos_N - 1][pos_M] == 0) search_campus(campus, visited, pos_N - 1, pos_M);

    if (pos_N + 1 != campus.size() && campus[pos_N + 1][pos_M] != 'X' && visited[pos_N + 1][pos_M] == 0) search_campus(campus, visited, pos_N + 1, pos_M);

    if (pos_M != 0 && campus[pos_N][pos_M - 1] != 'X' && visited[pos_N][pos_M - 1] == 0) search_campus(campus, visited, pos_N, pos_M - 1);

    if (pos_M + 1 != campus[0].size() && campus[pos_N][pos_M + 1] != 'X' && visited[pos_N][pos_M + 1] == 0) 
        search_campus(campus, visited, pos_N, pos_M + 1);
}

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    cin >> N >> M;

    vector<vector<char>> campus(N, vector<char>(M, 0));
    vector<vector<int>> visited(N, vector<int>(M, 0));

    int target_N, target_M;

    // 벡터에 값 입력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> campus[i][j];
            if(campus[i][j] == 'I') {
                target_N = i;
                target_M = j;
            }
        }
    }

    // 탐색 진행
    search_campus(campus, visited, target_N, target_M);

    // 결과 계산
    int result = 0;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if(campus[i][j] == 'P') result += visited[i][j];
        }
    }

    // 결과 출력
    if (result == 0) cout << "TT";
    else cout << result;

    return 0;
}