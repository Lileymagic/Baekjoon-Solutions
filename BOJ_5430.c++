// 문제
// 선영이는 주말에 할 일이 없어서 새로운 언어 AC를 만들었다. AC는 정수 배열에 연산을 하기 위해 만든 언어이다. 
// 이 언어에는 두 가지 함수 R(뒤집기)과 D(버리기)가 있다.

// 함수 R은 배열에 있는 수의 순서를 뒤집는 함수이고, D는 첫 번째 수를 버리는 함수이다. 
// 배열이 비어있는데 D를 사용한 경우에는 에러가 발생한다.

// 함수는 조합해서 한 번에 사용할 수 있다. 예를 들어, "AB"는 A를 수행한 다음에 바로 이어서 B를 수행하는 함수이다. 
// 예를 들어, "RDD"는 배열을 뒤집은 다음 처음 두 수를 버리는 함수이다.

// 배열의 초기값과 수행할 함수가 주어졌을 때, 최종 결과를 구하는 프로그램을 작성하시오.

// 입력
// 첫째 줄에 테스트 케이스의 개수 T가 주어진다. T는 최대 100이다.

// 각 테스트 케이스의 첫째 줄에는 수행할 함수 p가 주어진다. p의 길이는 1보다 크거나 같고, 100,000보다 작거나 같다.

// 다음 줄에는 배열에 들어있는 수의 개수 n이 주어진다. (0 ≤ n ≤ 100,000)

// 다음 줄에는 [x1,...,xn]과 같은 형태로 배열에 들어있는 정수가 주어진다. (1 ≤ xi ≤ 100)

// 전체 테스트 케이스에 주어지는 p의 길이의 합과 n의 합은 70만을 넘지 않는다.

// 출력
// 각 테스트 케이스에 대해서, 입력으로 주어진 정수 배열에 함수를 수행한 결과를 출력한다. 
// 만약, 에러가 발생한 경우에는 error를 출력한다.

#include <iostream>
#include <string>
#include <deque>
#include <algorithm>

using namespace std;

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T, n, num;
    string p;
    char trash;
    cin >> T;

    deque<int> dq; // 덱 선언
    bool mode, error;

    // 테스트 케이스만큼 반복
    for (int i = 0; i < T; i++) {
        cin >> p; // 수행할 함수 입력
        cin >> n; // 숫자의 개수 입력

        // 문자열에서 정수만 추출하기

        // 1. 대괄호 읽고 버리기
        dq.clear();
        cin >> trash;  

        // 2. n개의 숫자와 n-1개의 쉼표 버리기
        for (int j = 0; j < n; ++j) {
            cin >> num; // 숫자만 정확히 읽어옴
            dq.push_back(num);

            // 마지막 숫자가 아니라면 쉼표를 읽고 버리기
            if (j < n - 1) cin >> trash;
        }

        // 3. 끝나는 대괄호 읽고 버리기
        cin >> trash;


        // 문자열 p에 따라 작업 수행하기
        mode = true;
        error = false;
        for (char c : p) {
            // R일 때는 리스트 뒤집기
            if (c == 'R') mode = !mode;

            // D일 때는 맨 앞의 원소 버리기
            else {
                // 원소가 0개인데 D를 시도한다면 에러 출력
                if (dq.empty()) {
                    error = true;
                    break;
                }

                if (mode) dq.pop_front();
                else dq.pop_back();
            }
        }

        // 현재 리스트의 상태 출력하기
        if (error) {
            cout << "error\n";
            continue;
        }

        // 뒤집힌 상태일 경우 실제로 뒤집기
        if (!mode) reverse (dq.begin(), dq.end());

        // 내용 출력
        cout << "[";
        for (int k = 0; k < dq.size(); k++) {
                cout << dq[k];

                if (k < dq.size() - 1) cout << ",";
            }
        cout << "]\n";
    }

    return 0;
}