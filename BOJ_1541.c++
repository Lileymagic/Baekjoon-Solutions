// 문제
// 세준이는 양수와 +, -, 그리고 괄호를 가지고 식을 만들었다. 그리고 나서 세준이는 괄호를 모두 지웠다.

// 그리고 나서 세준이는 괄호를 적절히 쳐서 이 식의 값을 최소로 만들려고 한다.

// 괄호를 적절히 쳐서 이 식의 값을 최소로 만드는 프로그램을 작성하시오.

// 입력
// 첫째 줄에 식이 주어진다. 식은 ‘0’~‘9’, ‘+’, 그리고 ‘-’만으로 이루어져 있고, 
// 가장 처음과 마지막 문자는 숫자이다. 그리고 연속해서 두 개 이상의 연산자가 나타나지 않고, 
// 5자리보다 많이 연속되는 숫자는 없다. 수는 0으로 시작할 수 있다. 
// 입력으로 주어지는 식의 길이는 50보다 작거나 같다.

// 출력
// 첫째 줄에 정답을 출력한다.

#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <cctype>

using namespace std;

int main(void) {
    string s;
    cin >> s;

    vector<int> tokens_number;
    vector<string> tokens_operater;

    // 정규 표현식 정의
    regex pattern("(\\d+)|([\\+\\-])");

    // 정규표현식 매처 생성
    sregex_iterator begin(s.begin(), s.end(), pattern);
    sregex_iterator end;

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        string token = match.str();

        // 숫자라면 ?
        if (isdigit(token[0])) 
            tokens_number.push_back(stoi(match.str()));
        else 
            tokens_operater.push_back(match.str());
    }
    

    // 정답 계산
    int sum = tokens_number[0];
    int mSum = 0;
    bool inMinus = false;

    for (int i = 1; i < tokens_number.size(); i++) {
        // 연산자가 -일 때 
        if (tokens_operater[i - 1][0] == '-') {
            if (!inMinus) {
                inMinus = true; 
                mSum += tokens_number[i];
            } else {
                sum -= mSum;
                mSum = 0; mSum += tokens_number[i];
            }
        } else {
            if (inMinus) 
                mSum += tokens_number[i];
            else 
                sum += tokens_number[i];
        }
    }
    sum -= mSum;

    // 결과 출력
    cout << sum;

    return 0;
}