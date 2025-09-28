// 문제
// 자연수 N과 M이 주어졌을 때, 아래 조건을 만족하는 길이가 M인 수열을 모두 구하는 프로그램을 작성하시오.

// 1부터 N까지 자연수 중에서 중복 없이 M개를 고른 수열
// 고른 수열은 오름차순이어야 한다.
// 입력
// 첫째 줄에 자연수 N과 M이 주어진다. (1 ≤ M ≤ N ≤ 8)

// 출력
// 한 줄에 하나씩 문제의 조건을 만족하는 수열을 출력한다. 중복되는 수열을 여러 번 출력하면 안되며, 각 수열은 공백으로 구분해서 출력해야 한다.

// 수열은 사전 순으로 증가하는 순서로 출력해야 한다.

#include <iostream>
#include <cmath>

using namespace std;

void calc(int N, int M, int cur, int pattern, int stack) {
    int result;
    int div;

    for(int i = cur; i <= N - (M - 1); i++) {
        if (M == 1) {
            result = pattern * 10 + i;
            div = pow(10, stack - 1);

            for (int s = stack; s > 0; s--) {
                // // debug
                // cout << "cur div = " << div << " cur result = " << result << "   ";

                cout << result / div << " ";
                result %= div;  div /= 10;
            }
            cout << "\n";
        } else calc (N, M - 1, i + 1, pattern * 10 + i, stack + 1);
    }
}

int main(void) {
    int N, M;
    cin >> N >> M;

    calc(N, M, 1, 0, 1);

    return 0;
}