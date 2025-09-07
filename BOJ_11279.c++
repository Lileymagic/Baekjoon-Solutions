// 문제
// 널리 잘 알려진 자료구조 중 최대 힙이 있다. 최대 힙을 이용하여 다음과 같은 연산을 지원하는 프로그램을 작성하시오.

// 배열에 자연수 x를 넣는다.
// 배열에서 가장 큰 값을 출력하고, 그 값을 배열에서 제거한다.
// 프로그램은 처음에 비어있는 배열에서 시작하게 된다.

// 입력
// 첫째 줄에 연산의 개수 N(1 ≤ N ≤ 100,000)이 주어진다. 
// 다음 N개의 줄에는 연산에 대한 정보를 나타내는 정수 x가 주어진다. 
// 만약 x가 자연수라면 배열에 x라는 값을 넣는(추가하는) 연산이고, 
// x가 0이라면 배열에서 가장 큰 값을 출력하고 그 값을 배열에서 제거하는 경우이다. 
// 입력되는 자연수는 231보다 작다.

// 출력
// 입력에서 0이 주어진 횟수만큼 답을 출력한다. 만약 배열이 비어 있는 경우인데 가장 큰 값을 출력하라고 한 경우에는 0을 출력하면 된다.

#include <iostream>

using namespace std;

// 최대 힙
class maximum_heap {
private:
    int heap[100001];
    int count = 0;

    // 두 배열의 위치 바꾸기
    void change(int i, int j) {
        int tmp = heap[i];
        heap[i] = heap[j];
        heap[j] = tmp;
    }

    // 더 큰 값의 위치 반환하기
    int maximum (int i, int i_pos, int j, int j_pos) {
        if (i > j) return i_pos;
        else return j_pos;
    }

public:
    // 힙에 요소 삽입하기
    void insert(int x) {
        count++;
        heap[count] = x;

        int curNode = count;
        while (1) {
            if (curNode == 1) break;

            // 부모 노드보다 크다면 ?
            if (heap[curNode] > heap[curNode / 2]) {
                change(curNode, curNode / 2);
            }else break;

            curNode /= 2;
        }
    }
    
    // 힙 최상단의 요소 제거하기
    int pop() {
        if(count == 0) return 0;

        int returnValue = heap[1];
        heap[1] = heap[count];
        count--;

        int curNode = 1;
        while(1) {
            if (curNode * 2 > count) break;

            if (curNode * 2 + 1 <= count) {
                if (heap[curNode] < heap[curNode * 2] || heap[curNode] < heap[curNode * 2 + 1]) {
                    int max_pos = maximum(heap[curNode * 2], curNode * 2, heap[curNode * 2 + 1], curNode * 2 + 1);
                    change(curNode, max_pos);

                    curNode = max_pos;
                }else break;
            }else {
                if (heap[curNode] < heap[curNode * 2]){
                    int max_pos = curNode * 2;
                    change(curNode, max_pos);

                    curNode = max_pos;
                } else break;
            } 
        }

        return returnValue;
    }
};

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, x;
    cin >> N;
    
    // 연산 수행
    maximum_heap heap;
    for(int i = 0; i < N; i++) {
        cin >> x;

        if (x > 0) heap.insert(x);
        else cout << heap.pop() << "\n";
    }

    return 0;
}