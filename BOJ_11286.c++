// 문제
// 절댓값 힙은 다음과 같은 연산을 지원하는 자료구조이다.

// 배열에 정수 x (x ≠ 0)를 넣는다.
// 배열에서 절댓값이 가장 작은 값을 출력하고, 그 값을 배열에서 제거한다. 
// 절댓값이 가장 작은 값이 여러개일 때는, 가장 작은 수를 출력하고, 그 값을 배열에서 제거한다.
// 프로그램은 처음에 비어있는 배열에서 시작하게 된다.

// 입력
// 첫째 줄에 연산의 개수 N(1≤N≤100,000)이 주어진다. 
// 다음 N개의 줄에는 연산에 대한 정보를 나타내는 정수 x가 주어진다. 
// 만약 x가 0이 아니라면 배열에 x라는 값을 넣는(추가하는) 연산이고, 
// x가 0이라면 배열에서 절댓값이 가장 작은 값을 출력하고 그 값을 배열에서 제거하는 경우이다. 
// 입력되는 정수는 -231보다 크고, 231보다 작다.

// 출력
// 입력에서 0이 주어진 회수만큼 답을 출력한다. 
// 만약 배열이 비어 있는 경우인데 절댓값이 가장 작은 값을 출력하라고 한 경우에는 0을 출력하면 된다.

#include <iostream>

using namespace std;

// 정수를 절댓값으로 바꿈
long long int to_absolute(long long int x) {
    if (x > 0) return x;
    else return -x;
}

// a와 b의 절댓값을 비교해 작은 값을 출력
long long int compare_absolute(long long int a, long long int b) {
    if (to_absolute(a) < to_absolute(b)) return a;
    else if (to_absolute(a) > to_absolute(b)) return b;
    else {
        if (a > b) return b;
        else return a;
    }
}

// 절댓값 힙 클래스
class absolute_heap {
private:
    long long int heap[100001];
    int count = 0;

public:
    void push(int x) {
        count++;
        heap[count] = x;

        int cur_pos = count;
        long long int tmp;
        // 자식의 값이 부모보다 작다면
        while (cur_pos != 1 && compare_absolute(heap[cur_pos], heap[cur_pos / 2]) == heap[cur_pos]) {
            tmp = heap[cur_pos];
            heap[cur_pos] = heap[cur_pos / 2];
            heap[cur_pos/ 2] = tmp;
            cur_pos /= 2;
        }
    }

    long long int pop() {
        // 힙이 비었다면
        if (count == 0) return 0;

        long long int returnVal = heap[1];
        heap[1] = heap[count];
        count--;

        int cur_pos = 1;
        long long int tmp;
        // 부모의 값이 자식보다 크다면
        while (1) {
            if (cur_pos * 2 > count) break;

            if (cur_pos * 2 == count && compare_absolute(heap[cur_pos], heap[count]) == heap[count]) {
                tmp = heap[cur_pos];
                heap[cur_pos] = heap[count];
                heap[count] = tmp;
                cur_pos *= 2;
            } else if (compare_absolute(heap[cur_pos], heap[cur_pos * 2]) == heap[cur_pos * 2] || compare_absolute(heap[cur_pos], heap[cur_pos * 2 + 1]) == heap[cur_pos * 2 + 1]) {
                if (compare_absolute(heap[cur_pos * 2], heap[cur_pos * 2 + 1]) == heap[cur_pos * 2]) {
                    tmp = heap[cur_pos];
                    heap[cur_pos] = heap[cur_pos * 2];
                    heap[cur_pos * 2] = tmp;
                    cur_pos *= 2;
                } else {
                    tmp = heap[cur_pos];
                    heap[cur_pos] = heap[cur_pos * 2 + 1];
                    heap[cur_pos * 2 + 1] = tmp;
                    cur_pos = cur_pos * 2 + 1;
                }
            } else break;
        }
    
        return returnVal;
    }
};

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    // 힙에 값 입력
    absolute_heap heap;
    long long int x;
    
    for (int i = 0; i < N; i++) {
        cin >> x;
        
        if(x != 0) heap.push(x);
        else cout << heap.pop() << "\n";
    }

    return 0;
}