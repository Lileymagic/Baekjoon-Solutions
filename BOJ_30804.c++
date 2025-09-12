#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;


int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> tanghuru(N);

    // 과일 입력
    for (int fruit = 0; fruit < N; fruit++) {
        cin >> tanghuru[fruit]; 
    }

    
    // 정답 계산
    int max_length = 0;
    int left = 0;
    map<int,int> fruit_counts;
    
    // right 포인터를 한 칸씩 이동하며 윈도우를 확장
    for (int right = 0; right < N; right++) {
        // 현재 윈도우에 포함된 과일의 개수를 증가
        fruit_counts[tanghuru[right]]++;

        // 서로 다른 과일의 개수라 2개를 초과한다면
        while (fruit_counts.size() > 2) {
            // left 포인터를 오른쪽으로 이동해 윈도우 축소
            fruit_counts[tanghuru[left]]--;

            // 만약 해당 과일의 개수가 0개가 된다면 맵에서 삭제
            if (fruit_counts[tanghuru[left]] == 0) {
                fruit_counts.erase(tanghuru[left]);
            }
            left++;
        }

        // 현재 유효한 길이를 계산하고, 최댓값을 갱신
        max_length = max(max_length, right - left + 1);
    }

    cout << max_length;
    
    return 0;
}