#include <iostream>
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