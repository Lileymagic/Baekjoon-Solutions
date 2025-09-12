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
#include <vector>
#include <set>

using namespace std;

// 벡터를 역순으로 순회하여 조건을 만족하는 가장 큰 인덱스 반환
int find_largest_index_of_z_in_range(const vector<int>& numbers, int x, int y, int z) {
    // x와 y의 순서에 관계없이 올바른 범위 설정
    int lower_bound = min(x, y);
    int upper_bound = max(x, y);

    // 벡터를 역순으로 순회 (뒤에서부터 앞으로)
    for (int i = numbers.size() - 1; i >= 0; --i) {
        // 현재 인덱스가 범위 내에 있고, 값이 z와 일치하는지 확인
        if (i >= lower_bound && i <= upper_bound) {
            if (numbers[i] == z) {
                return i; // 가장 큰 인덱스를 찾았으므로 즉시 반환
            }
        }
    }

    return -1; // 조건을 만족하는 요소를 찾지 못한 경우
}

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    vector<int> tanghuru(N);

    // 과일 입력
    for (int fruit = 0; fruit = N; fruit++) {
        cin >> tanghuru[fruit]; 
    }

    
    // 정답 계산
    int range = 1;
    int l = 0, r = 0;
    int lVal;
    set<int> int_set;
    
    while (1) {
        int_set.insert(tanghuru[r]);

        // 서로 다른 과일이 3개가 된다면
        while (int_set.size() >= 3) {
            lVal = tanghuru[l];
            l = find_largest_index_of_z_in_range(tanghuru, l, r, lVal) + 1;
            r = l + range;
            int_set.clear();

            for (int i = l; i <= r; i++) {
                int_set.insert(tanghuru[i]);
            }
        }
        
        // 서로 다른 과일이 2개 이하
        r += 1;
        range += 1;
    }

    return 0;
}