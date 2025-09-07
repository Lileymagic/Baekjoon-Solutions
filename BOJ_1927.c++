// 문제
// 널리 잘 알려진 자료구조 중 최소 힙이 있다. 
// 최소 힙을 이용하여 다음과 같은 연산을 지원하는 프로그램을 작성하시오.

// 배열에 자연수 x를 넣는다.
// 배열에서 가장 작은 값을 출력하고, 그 값을 배열에서 제거한다.
// 프로그램은 처음에 비어있는 배열에서 시작하게 된다.

// 입력
// 첫째 줄에 연산의 개수 N(1 ≤ N ≤ 100,000)이 주어진다. 
// 다음 N개의 줄에는 연산에 대한 정보를 나타내는 정수 x가 주어진다. 
// 만약 x가 자연수라면 배열에 x라는 값을 넣는(추가하는) 연산이고, 
// x가 0이라면 배열에서 가장 작은 값을 출력하고 그 값을 배열에서 제거하는 경우이다. 
// x는 231보다 작은 자연수 또는 0이고, 음의 정수는 입력으로 주어지지 않는다.

// 출력
// 입력에서 0이 주어진 횟수만큼 답을 출력한다. 
// 만약 배열이 비어 있는 경우인데 가장 작은 값을 출력하라고 한 경우에는 0을 출력하면 된다.

#include <iostream>

using namespace std;

// 최소 힙 클래스
class minimum_heap {
private:
    long long heap[100001];
    int count = 0;

    // 두 노드의 위치 바꾸기
    void change(int p, int s) {
        long long tmp = heap[p];
        heap[p] = heap[s];
        heap[s] = tmp;
    }

public:
    // 생성자
    minimum_heap() {}

    // 힙에 값 삽입하기
    void insert(long long N) {
        count++;
        heap[count] = N;

        int pos = count;
        while(1) {
            if(pos == 1) break;

            // 부모 노드보다 작다면
            if (heap[pos] < heap[pos/2]) {
                change(pos, pos/2);
                pos = pos/2;
            } else break;
        }
    }
 
    // 힙의 root 반환 후 제거
    long long pop() {
        // 크기가 0일 때
        if(count == 0) return 0;

        long long root = heap[1];
        heap[1] = heap[count];
        count--;

        int pos = 1;
        int tmp;
        while(1) {
            if (count/2 < pos) break;

            // 부모가 자식 노드보다 크다면
            if ((pos * 2 + 1) <= count) {
                if (heap[pos] > heap[pos * 2] || heap[pos] > heap[pos * 2 + 1]) {
                    if (heap[pos * 2] > heap[pos * 2 + 1])  tmp = pos * 2 + 1;
                    else tmp = pos * 2;

                    change(pos, tmp);
                    pos = tmp;
                } else break;
            } else if (heap[pos] > heap[pos * 2]){
                tmp = pos * 2;
                change(pos, tmp);
                pos = tmp;
            } else break;
        }
        
        return root;
    }
};

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    minimum_heap heap;
    int N;
    cin >> N;

    // 연산 수행
    long long x;
    for (int i = 0; i < N; i++) {
        cin >> x;

        if(x > 0) heap.insert(x);
        else cout << heap.pop() << "\n";
    }
    
    return 0;
}