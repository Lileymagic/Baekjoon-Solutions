#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int getPowerOfTwo_Log(long long int n) {
    int result = -1;
    long long int val = 1;

    while (n >= val) {
        result++;
        val *= 2;
    }

    return result;
}

// 이중 우선순위 큐
class duplicate_priority_queue {
private:
    long long int array[1000002];
    int cnt = 1;

public:
    void push(long long int i) {
        array[cnt] = i;
        cnt++;

        // 자식 노드가 부모 노드보다 작을 때
        int cur_node = cnt - 1;
        while(cur_node != 1 && array[cur_node] < array[cur_node / 2]) {
            int temp = array[cur_node];
            array[cur_node] = array[cur_node / 2];
            array[cur_node / 2] = temp;

            cur_node = cur_node / 2;
        }
    }

    void pop_max() {
        if (cnt <= 1) return; 

        // (추가) 가장 큰 노드 찾기
        int power = (int)pow(2, getPowerOfTwo_Log(cnt - 1));
        if (cnt == 2) power = 1;

        int max_pos = power;
        for (int i = power; i < cnt; i++) {
            if (array[max_pos] < array[i]) max_pos = i;
        }

        array[max_pos] = array[cnt - 1];
        cnt--;
    }

    void pop_min() {
        if (cnt <= 1) return; 

        cnt--;
        long long int dum = array[1];
        array[1] = array[cnt];
        
        // (추가) 부모 노드가 자식 노드보다 클 때
        int cur_node = 1;
        while(1) {
            if (cur_node * 2 > cnt - 1) break;
            else if (cur_node * 2 == cnt - 1) {
                if (array[cur_node] < array[cnt - 1]) break;
                else {
                    long long int temp = array[cur_node];
                    array[cur_node] = array[cnt - 1];
                    array[cnt - 1] = temp;
                    break;
                }
            } else {
                if (array[cur_node] > array[cur_node * 2] || array[cur_node] > array[cur_node * 2 + 1]) {
                    if (array[cur_node * 2] <= array[cur_node * 2 + 1]) {
                        long long int temp = array[cur_node];
                        array[cur_node] = array[cur_node * 2];
                        array[cur_node * 2] = temp;
                        cur_node *= 2;
                    } else {
                        long long int temp = array[cur_node];
                        array[cur_node] = array[cur_node * 2 + 1];
                        array[cur_node * 2 + 1] = temp;
                        cur_node = cur_node * 2 + 1;
                    }
                } else break;
            }
        }
    }

    long long int front() {
        if (cnt <= 1) throw runtime_error("front() called on empty queue");
        return array[1];
    }

    long long int back() {
        if (cnt <= 1) throw runtime_error("back() called on empty queue");

        int power = (int)pow(2, getPowerOfTwo_Log(cnt - 1));
        if (cnt == 2) power = 1;

        int max_pos = power;
        for (int i = power; i < cnt; i++) {
            if (array[max_pos] < array[i]) max_pos = i;
        }

        return array[max_pos];
    }

    bool empty() {
        return cnt == 1;
    }

    void clear() {
        cnt = 1;
    }
};

int main(void) {
    // 기본 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T, k;
    long long int n;
    char c;
    cin >> T;

    // 결과 계산
    duplicate_priority_queue q;
    for (int i = 0; i < T; i++) {
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> c;   cin >> n;
            switch(c){
                case 'I':
                    q.push(n);
                    break;

                case 'D':
                    if (n == 1 && !q.empty()) q.pop_max();

                    if (n == -1 && !q.empty()) q.pop_min();
            }
        }

        if (!q.empty()) cout << q.back() << " " << q.front() << "\n";
        else cout << "EMPTY\n";
        q.clear();
    }

    return 0;
}