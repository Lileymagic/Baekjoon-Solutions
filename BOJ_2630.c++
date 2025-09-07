// 문제
// 아래 <그림 1>과 같이 여러개의 정사각형칸들로 이루어진 정사각형 모양의 종이가 주어져 있고, 
// 각 정사각형들은 하얀색으로 칠해져 있거나 파란색으로 칠해져 있다. 
// 주어진 종이를 일정한 규칙에 따라 잘라서 다양한 크기를 가진 정사각형 모양의 하얀색 또는 파란색 색종이를 만들려고 한다.



// 전체 종이의 크기가 N×N(N=2k, k는 1 이상 7 이하의 자연수) 이라면 종이를 자르는 규칙은 다음과 같다.

// 전체 종이가 모두 같은 색으로 칠해져 있지 않으면 가로와 세로로 중간 부분을 잘라서 
// <그림 2>의 I, II, III, IV와 같이 똑같은 크기의 네 개의 N/2 × N/2색종이로 나눈다. 
// 나누어진 종이 I, II, III, IV 각각에 대해서도 앞에서와 마찬가지로 모두 같은 색으로 칠해져 있지 않으면 
// 같은 방법으로 똑같은 크기의 네 개의 색종이로 나눈다. 
// 이와 같은 과정을 잘라진 종이가 모두 하얀색 또는 모두 파란색으로 칠해져 있거나, 
// 하나의 정사각형 칸이 되어 더 이상 자를 수 없을 때까지 반복한다.

// 위와 같은 규칙에 따라 잘랐을 때 <그림 3>은 <그림 1>의 종이를 처음 나눈 후의 상태를, 
// <그림 4>는 두 번째 나눈 후의 상태를, <그림 5>는 최종적으로 만들어진 다양한 크기의 9장의 하얀색 색종이와 7장의 파란색 색종이를 보여주고 있다.



// 입력으로 주어진 종이의 한 변의 길이 N과 각 정사각형칸의 색(하얀색 또는 파란색)이 주어질 때 
// 잘라진 하얀색 색종이와 파란색 색종이의 개수를 구하는 프로그램을 작성하시오.

// 입력
// 첫째 줄에는 전체 종이의 한 변의 길이 N이 주어져 있다. 
// N은 2, 4, 8, 16, 32, 64, 128 중 하나이다. 
// 색종이의 각 가로줄의 정사각형칸들의 색이 윗줄부터 차례로 둘째 줄부터 마지막 줄까지 주어진다. 
// 하얀색으로 칠해진 칸은 0, 파란색으로 칠해진 칸은 1로 주어지며, 각 숫자 사이에는 빈칸이 하나씩 있다.

// 출력
// 첫째 줄에는 잘라진 햐얀색 색종이의 개수를 출력하고, 둘째 줄에는 파란색 색종이의 개수를 출력한다.

#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

// 종이 정보
class node {
public:
    int parent_x;
    int parent_y;

    int color;

    // 생성자
    node(int x, int y, int color) : parent_x(x), parent_y(y), color(color) {};
};

// 만들 수 있는 가장 큰 색종이의 범위를 반환
int iscolorSame (vector<vector<node>>& paper, int x, int y) {
    // parent가 자신이 아니라면 (종속됐다면) 넘기기
    if (paper[x][y].parent_x != x || paper[x][y].parent_y != y) {
        return 0;
    }

    // 색깔이 같은지 검사
    int value = 1;
    int range = 2;
    int curColor = paper[x][y].color;

    while (1) {
        if (paper.size() < x + range || paper.size() < y + range) return value;

        for (int i = x; i < range + x; i++) {
            for (int j = y; j < range + y; j++) {
                // 색깔이 다르다면
                if (curColor != paper[i][j].color) return value; 
                // 종속됐다면
                if (paper[i][j].parent_x != i || paper[i][j].parent_y != j) return value;
            }
        }
        value *= 2; range*= 2;
    }
}

// 구간 합치기
void merge (vector<vector<node>>& paper, int x, int y, int size) {
    int target_x;
    int target_y;

    target_x = paper[x][y].parent_x;
    target_y = paper[x][y].parent_y;

    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            paper[i][j].parent_x = target_x;
            paper[i][j].parent_y = target_y;
        }
    }
}

// 색종이 자르기
vector<vector<node>> cut_paper(vector<vector<node>>& paper) {
    int maximum = paper.size() - 1;
    int size = maximum;

    while (1) {
        for (int i = 1; i < paper.size(); i += size) {
            for (int j = 1; j < paper.size(); j += size) {
                merge(paper, i, j, iscolorSame(paper, i, j));
            }
        }
        if (size == 2) break;
        
        size /= 2;
    }

    return paper;
}

// 좌표 비교를 위한 구조체
struct coordinates {
    int x;
    int y;

    // 비교 연산자 오버로딩
    bool operator<(const coordinates& other) const {
        if (x != other.x) {
            return x < other.x;
        }
        return y < other.y;
    }
};

int main(void) {
    // 기본 설정
    int N;
    cin >> N;

    // 색상 입력
    vector<vector<node>> paper(N + 1, vector<node>(N + 1, node(0, 0, 0)));
    int color;

    for (int i = 1; i <=N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> color;

            paper[i][j] = node(i, j, color);
        }
    }

    // 색종이 자르기
    paper = cut_paper(paper);


    // 벡터를 순회하며 데이터 그룹화
    map<int, set<coordinates>> color_coords;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            const node& current_node = paper[i][j];

            // 좌표 정보를 삽입
            coordinates current_coords = {current_node.parent_x, current_node.parent_y};
            color_coords[current_node.color].insert(current_coords);
        }
    }

    // 정답 출력
    cout << color_coords[0].size() << endl << color_coords[1].size();

    return 0;
}