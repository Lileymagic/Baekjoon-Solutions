// 문제
// N+1개의 I와 N개의 O로 이루어져 있으면, I와 O이 교대로 나오는 문자열을 PN이라고 한다.

// P1 IOI
// P2 IOIOI
// P3 IOIOIOI
// PN IOIOI...OI (O가 N개)
// I와 O로만 이루어진 문자열 S와 정수 N이 주어졌을 때, S안에 PN이 몇 군데 포함되어 있는지 구하는 프로그램을 작성하시오.

// 입력
// 첫째 줄에 N이 주어진다. 둘째 줄에는 S의 길이 M이 주어지며, 셋째 줄에 S가 주어진다.

// 출력
// S에 PN이 몇 군데 포함되어 있는지 출력한다.

// 제한
// 1 ≤ N ≤ 1,000,000
// 2N+1 ≤ M ≤ 1,000,000
// S는 I와 O로만 이루어져 있다.

#include <iostream>
#include <string>

using namespace std;

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long N, M;
    string S;

    cin >> N >> M >> S;

    // 정답 계산
    long long result = 0;
    long long stack, count;

    // 반복문을 이용해 string 전체를 순회하며 계산
    for (long long i = 0; i < M; i++) {
        if (S[i] == 'I') {
            stack = 1; 
            while (1) {
                // 인덱스 범위를 벗어난다면 종료
                if (i + stack >= M) break;

                // IOIOI .. 형식이 계속 반복된다면 stack 증가
                if (stack % 2 == 1 && S[stack + i] == 'O') stack++;
                else if (stack % 2 == 0 && S[stack + i] == 'I') stack++;
                else break;
            }

            count = (stack - 1) / 2 - N + 1;
            if (count > 0) result += count;

            i += stack - 1;
        }
    }

    // 값 출력
    cout << result;

    return 0;
}



