//문제

// 신종 바이러스인 웜 바이러스는 네트워크를 통해 전파된다. 
// 한 컴퓨터가 웜 바이러스에 걸리면 그 컴퓨터와 네트워크 상에서 연결되어 있는 모든 컴퓨터는 웜 바이러스에 걸리게 된다.

// 예를 들어 7대의 컴퓨터가 <그림 1>과 같이 네트워크 상에서 연결되어 있다고 하자. 
// 1번 컴퓨터가 웜 바이러스에 걸리면 웜 바이러스는 2번과 5번 컴퓨터를 거쳐 
// 3번과 6번 컴퓨터까지 전파되어 2, 3, 5, 6 네 대의 컴퓨터는 웜 바이러스에 걸리게 된다. 
// 하지만 4번과 7번 컴퓨터는 1번 컴퓨터와 네트워크상에서 연결되어 있지 않기 때문에 영향을 받지 않는다.

// 어느 날 1번 컴퓨터가 웜 바이러스에 걸렸다. 
// 컴퓨터의 수와 네트워크 상에서 서로 연결되어 있는 정보가 주어질 때, 
// 1번 컴퓨터를 통해 웜 바이러스에 걸리게 되는 컴퓨터의 수를 출력하는 프로그램을 작성하시오.

#include <stdio.h>
#include <stdlib.h>

// 그래프의 간선
typedef struct GraphNode{
    int vertex; // 연결된 정점의 번호
    struct GraphNode* link; 
} GraphNode;

// 그래프 구조체
typedef struct GraphType {
    int n; // 정점의 개수
    GraphNode* adj_list[101]; // 인접 리스트 배열
} GraphType;

// 방문 여부를 기록할 배열
int visited[101];

// 그래프 초기화 함수
void init(int n, GraphType* g) {
    g->n = n;

    for(int i = 0; i < n + 1; i++) {
        g->adj_list[i] = NULL;
        visited[i] = 0;

    }
}

// 간선 삽입 함수 (양방향 그래프 가정)
void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node;

    // u에서 v로의 간선 추가
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->link = g->adj_list[u];
    g->adj_list[u] = node;

    // v에서 u로의 간선 추가 (양방향)
    node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = u;
    node->link = g->adj_list[v];
    g->adj_list[v] = node;
}

// dfs 순회 함수
void dfs(GraphType* g, int v) {
    visited[v] = 1; // 현재 방문 정점 표시

    // 인접한 정점을 재귀적으로 탐색
    GraphNode* n;
    for (n = g->adj_list[v]; n; n = n->link) {
        // 인접한 정점이 아직 방문되지 않았다면
        if(!visited[n->vertex]) {
           dfs(g, n->vertex); // 재귀 호출 
        }
    }
}

// 메인 함수
int main() {
    int n, links; // 컴퓨터의 수, 간선의 수

    // 기본 설정
    scanf("%d", &n);
    scanf("%d", &links);

    // 그래프 생성
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    
    init(n, g);

    // 간선 삽입
    int u, v; // 연결될 간선 u, v

    for (int i = 0; i < links; i++) {
        scanf("%d %d", &u, &v);
        insert_edge(g, u, v);
    }

    // dfs 순회
    dfs(g, 1);

    // 바이러스에 걸리게 되는 컴퓨터의 수 출력
    int infected = 0; // 감염된 컴퓨터의 개수
    for (int i = 0; i < n + 1; i++) {
        if(visited[i]) infected++;
    }

    // 1번 본인은 감염된 수에서 제외
    printf("%d", infected - 1);

    // 메모리 해제
    for(int i = 0; i < n + 1; i++) {
        GraphNode*p = g->adj_list[i];
        while (p != NULL) {
            GraphNode* temp = p;
            p = p->link;
            free(temp);
        }
    }
    free(g);

    return 0;
}