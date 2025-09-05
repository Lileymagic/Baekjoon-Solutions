// 문제
// 차세대 영농인 한나는 강원도 고랭지에서 유기농 배추를 재배하기로 하였다. 
// 농약을 쓰지 않고 배추를 재배하려면 배추를 해충으로부터 보호하는 것이 중요하기 때문에, 
// 한나는 해충 방지에 효과적인 배추흰지렁이를 구입하기로 결심한다. 
// 이 지렁이는 배추근처에 서식하며 해충을 잡아 먹음으로써 배추를 보호한다. 
// 특히, 어떤 배추에 배추흰지렁이가 한 마리라도 살고 있으면 이 지렁이는 인접한 다른 배추로 이동할 수 있어, 
// 그 배추들 역시 해충으로부터 보호받을 수 있다. 
// 한 배추의 상하좌우 네 방향에 다른 배추가 위치한 경우에 서로 인접해있는 것이다.

// 한나가 배추를 재배하는 땅은 고르지 못해서 배추를 군데군데 심어 놓았다. 
// 배추들이 모여있는 곳에는 배추흰지렁이가 한 마리만 있으면 되므로 
// 서로 인접해있는 배추들이 몇 군데에 퍼져있는지 조사하면 총 몇 마리의 지렁이가 필요한지 알 수 있다. 
// 예를 들어 배추밭이 아래와 같이 구성되어 있으면 최소 5마리의 배추흰지렁이가 필요하다.
//  0은 배추가 심어져 있지 않은 땅이고, 1은 배추가 심어져 있는 땅을 나타낸다.

// 1	1	0	0	0	0	0	0	0	0
// 0	1	0	0	0	0	0	0	0	0
// 0	0	0	0	1	0	0	0	0	0
// 0	0	0	0	1	0	0	0	0	0
// 0	0	1	1	0	0	0	1	1	1
// 0	0	0	0	1	0	0	1	1	1
// 입력
// 입력의 첫 줄에는 테스트 케이스의 개수 T가 주어진다. 
// 그 다음 줄부터 각각의 테스트 케이스에 대해 
// 첫째 줄에는 배추를 심은 배추밭의 가로길이 M(1 ≤ M ≤ 50)과 세로길이 N(1 ≤ N ≤ 50), 
// 그리고 배추가 심어져 있는 위치의 개수 K(1 ≤ K ≤ 2500)이 주어진다. 
// 그 다음 K줄에는 배추의 위치 X(0 ≤ X ≤ M-1), Y(0 ≤ Y ≤ N-1)가 주어진다. 두 배추의 위치가 같은 경우는 없다.

// 출력
// 각 테스트 케이스에 대해 필요한 최소의 배추흰지렁이 마리 수를 출력한다. 

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;

// 배추의 좌표
typedef struct point {
    int x;
    int y;

    // 생성자
    point(int x, int y) {
        this->x = x;
        this->y = y;
    }
}point;

// 유니온-파인드 자료구조
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    vector<point> infomation;
    set<int> roots_set;

public:
    // 생성자
    UnionFind() {}

    // 부모 노드 찾기
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }

        return parent[i] = find(parent[i]);
    }

    // 두 집합 합치기
    void unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            if (rank[root_i] < rank[root_j]) {
                parent[root_i] = root_j; 
            } else if (rank[root_i] > rank[root_j]) {
                parent[root_j] = root_i;
            } else {
                parent[root_j] = root_i;
                rank[root_i]++;
            }
        }
    }

    // x,y의 좌표를 가지는 노드가 있는지 확인하고, 있다면 인덱스 반환
    int put_index(int x, int y) {
        auto it = find_if(infomation.begin(), infomation.end(), [x, y](point num) {
            return (num.x == x && num.y == y);
        });

        // 찾는 좌표에 노드가 없다면
        if (it == infomation.end()) {
            return -1;
        }
        
        int index = distance(infomation.begin(), it);

        // 인덱스 반환하기
        return index;
    }

    // 삽입하기
    void insert(int x, int y) {
        infomation.push_back(point(x, y));
        parent.push_back(infomation.size() - 1);
        rank.push_back(0);

        // 상하좌우 4개의 노드가 있는지 확인하고, 있다면 병합하기 
        int index;
        int current_index = parent.size() - 1;
        index = put_index(x + 1, y);
        if (index != -1) {
            unite(current_index, index);
        }

        index = put_index(x - 1, y);
        if (index != -1) {
            unite(current_index, index);
        }

        index = put_index(x, y + 1);
        if (index != -1) {
            unite(current_index, index);
        }

        index = put_index(x, y - 1);
        if (index != -1) {
            unite(current_index, index);
        }
    }

    // 두 노드가 연결되어 있는지 확인하기
    bool connected(int i, int j) {
        return find(i) == find(j);
    }

    // 루트의 개수 확인하기
    int howManyRoots() {
        roots_set.clear();

        // 모든 원소를 순회하며 각 원소의 최종 루트 찾기
        for (int i = 0; i < parent.size(); ++i) {
            int root = find(i);
            roots_set.insert(root);
        }
    
        return roots_set.size();
    }
};

int main(void) {
    // 기본 설정
    int T; // 테스트 케이스의 개수
    cin >> T;

    int M, N, K; // 배추밭의 가로길이, 세로길이, 배추의 개수
    int x,y; // 배추의 x,y좌표

    // 배추밭의 정보 입력
    for(int i = 0; i < T; i++) {
        cin >> M >> N >> K;
        UnionFind unionfind;

        // 배추의 위치 입력
        for(int j = 0; j < K; j++) {
            cin >> x >> y;
            unionfind.insert(x, y);
        }

        // 값 출력하기
        cout << unionfind.howManyRoots() << endl;
    }

    return 0;
}