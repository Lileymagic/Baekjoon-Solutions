// 문제
// 수빈이는 동생과 숨바꼭질을 하고 있다. 
// 수빈이는 현재 점 N(0 ≤ N ≤ 100,000)에 있고, 동생은 점 K(0 ≤ K ≤ 100,000)에 있다. 
// 수빈이는 걷거나 순간이동을 할 수 있다. 
// 만약, 수빈이의 위치가 X일 때 걷는다면 1초 후에 X-1 또는 X+1로 이동하게 된다. 
// 순간이동을 하는 경우에는 1초 후에 2*X의 위치로 이동하게 된다.

// 수빈이와 동생의 위치가 주어졌을 때, 
// 수빈이가 동생을 찾을 수 있는 가장 빠른 시간이 몇 초 후인지 구하는 프로그램을 작성하시오.

// 입력
// 첫 번째 줄에 수빈이가 있는 위치 N과 동생이 있는 위치 K가 주어진다. N과 K는 정수이다.

// 출력
// 수빈이가 동생을 찾는 가장 빠른 시간을 출력한다.

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

int calc(int N, int K) {
    int result = 0;

    if (N >= K) {
            // printf("calc(%d, %d)의 결과는 %d 입니다\n", N, K, N - K);
            return N - K;
        }

    if (N - 1 == K || N + 1 == K) {
        // printf("calc(%d, %d)의 결과는 1 입니다\n", N, K);
        return 1;
    }

    // K가 짝수, 홀수
    if (K % 2 == 0) {
        result = min(calc(N, K / 2) + 1, K - N);
    } else {
        result = min(min(calc(N, K / 2) + 2, calc(N, K / 2 + 1) + 2), K - N);  
    }

    // printf("calc(%d, %d)의 결과는 %d 입니다\n", N, K, result);
    return result;
}

int main(void) {
    // 기본 설정
    int N, K;
    cin >> N >> K;

    // 정답 계산
    int time = 0;
    
    time = calc(N, K);

    // 답 출력
    cout << time;

    return 0;
}