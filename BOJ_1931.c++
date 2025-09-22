#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 회의 시간 구조체
typedef struct task {
    long long start;
    long long end;

    // 생성자
    task() : start(0), end(0) {}
    task(long long start, long long end): start(start), end(end) {}
}task;

// 비교 함수 
bool compare(const task& a, const task& b) {
    // end 값이 작은 것이 앞으로 오도록 (오름차순)
    if (a.end == b.end) return a.start < b.start;
    return a.end < b.end;
}

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;
    vector<task> vector_task(N);
    
    int start, end;
    for (task& t : vector_task) {
        cin >> t.start;
        cin >> t.end;
    }

    // 정렬
    sort(vector_task.begin(), vector_task.end(), compare);
    
    int cnt = 0;
    long long cur_end_time = 0;

    // 정답 계산
    for (task t : vector_task) {
        // cout << "current  t.start = " << t.start << "   current t.end = " << t.end << "  current cur_time = " << cur_end_time << endl;

        if (cur_end_time <= t.end && cur_end_time <= t.start ) {
            cur_end_time = t.end;
            cnt++;
        }
    }

    cout << cnt;
    return 0;
}
