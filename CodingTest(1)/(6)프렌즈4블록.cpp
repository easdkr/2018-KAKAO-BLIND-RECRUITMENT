/*
입력값이 최대 30X30으로 작기 때문에 완전탐색으로 해결하는 문제였다. 
삭제하고 밑으로 내려주는걸 어떻게 구현해야할지 고민하다 시간이 오래걸렸는데
그냥 스택을 하나써서 삭제되지 않은 블럭끼리 쌓아주는 것으로 해결했다. 
*/
#include <string>
#include <vector>
#include <stack>
using namespace std;
const int directionY[4] = { 0, 0, 1, 1 };
const int directionX[4] = { 0, 1, 0, 1 };
vector<vector<pair<char, bool>>> createFriendsBoard(int m, int n, vector<string>& board);
int searchFourBlock(int m, int n, vector<vector<pair<char, bool>>>& board);
void eraseBlock(vector<vector<pair<char, bool>>>& board, int height, int width);
int solution(int m, int n, vector<string> board) {
	int answer = 0;
    //<블록타입, 삭제유무>의 벡터 
	auto friendsBoard = createFriendsBoard(m, n, board);
	while (true) {
		int erasedNum = searchFourBlock(m, n, friendsBoard);
		if (erasedNum == 0)
			break;
		else {
			answer += erasedNum;
			eraseBlock(friendsBoard, m, n);
		}
	}
	return answer;
}
//<블록캐릭터, 삭제유무> 쌍의 벡터로 만든다
vector<vector<pair<char, bool>>> createFriendsBoard(int m, int n, vector<string>& board) {
	vector<vector<pair<char, bool>>> ret;
	//<블록캐릭터, 삭제유무> 쌍의 벡터로 만든다
	ret = vector<vector<pair<char, bool>>>(m, vector<pair<char, bool>>(n));
	for (int y = 0; y < m; ++y)
		for (int x = 0; x < n; ++x)
			ret[y][x] = make_pair(board[y][x], false);
	return ret;
}
//board의 제거할 수 있는 블럭을 표시하고 제거되는 블럭의 수를 반환한다. 
int searchFourBlock(int m, int n, vector<vector<pair<char, bool>>>& board) {
	int erasedNum = 0;
	for (int y = 0; y < m-1; ++y) {
		for (int x = 0; x < n-1; ++x) {
			//지워진 블럭이면 그냥 넘어간다. 
			if (board[y][x].first == ' ')
				continue;
			char blockChar = board[y][x].first;
			//4방향이 모두 같으면 지워야하는 블럭이라고 표시한다.
			if (blockChar == board[y + 1][x].first && blockChar == board[y + 1][x + 1].first
				&& blockChar == board[y][x + 1].first) {
				for (int i = 0; i < 4; ++i) {
					auto& eraseBlock = board[y + directionY[i]][x + directionX[i]];
					//아직 지워지지 않은 블럭이면 지워진 개수 추가
					if (eraseBlock.second == false)
						++erasedNum;
					//지워졌다고 표시 
					eraseBlock.second = true;
				}
			}
		}
	}
	return erasedNum;
}
//블럭을 제거하고 아래로 내려준다.
void eraseBlock(vector<vector<pair<char, bool>>>& board, int height, int width) {
	stack<pair<char, bool>> s;
	for (int x = 0; x < width; ++x) {
		//삭제되지 않을 블럭을 아래부터 순서대로 스택에 채운다
		for (int y = height - 1; y >= 0; --y) {
			if (!board[y][x].second)
				s.push(make_pair(board[y][x].first, false));
		}
		//나머지부분을 모두 삭제된 블럭으로 채운다
		while (s.size() != height)
			s.push(make_pair(' ', true));
		//다시 board에 넣어준다. 
		for (int y = 0; y < height; ++y) {
			board[y][x] = s.top();
			s.pop();
		}
	}
}