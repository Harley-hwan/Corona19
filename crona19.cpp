#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

int n;
char ch[26]; // 알파벳
vector<int> v[26];
bool visit[26] = { 0, }; // 방문 배열
int sum[26] = { 0, };
stack<int> s; // 방문하는 마을 번호,
inline void dfs() {
	while(!s.empty()){
		int node = s.top(); s.pop();
		int _size = v[node].size();
		for (int i = 0; i < _size; i++) {
			int conn = v[node][i];
			if (!visit[conn]) {
				visit[conn] = 1;
				s.push(conn);
			}
		}
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> ch[i];
		for (int j = 0; j < n; j++) {
			int num;
			cin >> num;
			if (num) {
				v[i].push_back(j);
			}
			sum[i] += num; // 의 합
		}
	}
	int last;
	cin >> last; // -1 입력 
	int answer = 0;
	char Canswer;
	for (int i = 0; i < n; i++) { // i번째 마을을 폐쇄시키면서 답을 구해나감
		fill(visit, visit + 26, 0); // 매 수행시 방문 노드 초기화
		visit[i] = 1; // 방문 못하도록 미리 방문처리
		int turn = 0; // 탐색을 몇번 진행했는지
		for (int j = 0; j < n; j++) {
			if (!visit[j]) { // 아직 방문하지 않은 마을부터 탐색을 시작
				// 최종적으로 여기 두번 이상 들어온다면 완전히 분리가 된것임
				turn += 1;
				visit[j] = 1;
				s.push(j);
				dfs();
			}
		}
		if (turn >= 2) { // 탐색을 2번이상 돌았음 = i번 마을을 폐쇄시키면 2개 이상의
			// 마을로 나눌수 있다는것을 의미함
			if (answer < sum[i]) { // 계속 구해온 최대값보다
				// i번째 마을의 유동인구의 합이 더 크면
				answer = sum[i]; // 갱신
				Canswer = ch[i]; // 마을에 해당하는 알파벳
			}
		}
	}
	cout << Canswer;
}