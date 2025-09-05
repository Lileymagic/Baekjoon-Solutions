// 문제
// 수 N개가 주어졌을 때, i번째 수부터 j번째 수까지 합을 구하는 프로그램을 작성하시오.

// 입력
// 첫째 줄에 수의 개수 N과 합을 구해야 하는 횟수 M이 주어진다. 둘째 줄에는 N개의 수가 주어진다. 
// 수는 1,000보다 작거나 같은 자연수이다. 셋째 줄부터 M개의 줄에는 합을 구해야 하는 구간 i와 j가 주어진다.

// 출력
// 총 M개의 줄에 입력으로 주어진 i번째 수부터 j번째 수까지 합을 출력한다.

#include <iostream>

using namespace std;

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M;
    long long arr_sum[100000];  //누적합

    cin >> N >> M;

    // 배열에 값 설정
    int value;
    long long sum = 0;
    for(int i = 0; i < N; i++) {
        cin >> value;
        sum += value;
        arr_sum[i] = sum;
    }

    // 수의 구간합 계산, 출력
    int i, j;
    for(int k = 0; k < M; k++) {
        cin >> i >> j;

        // 값 출력
        if (i != 1)
            cout << arr_sum[j - 1] - arr_sum[i - 2] << "\n";
        else
            cout << arr_sum[j - 1] << "\n";
    }

    return 0;
}