/*
점수와 옵션 별로 어떻게 자를까 고민하다 
숫자만 스택에 넣는 것으로 구현을 했다. 
약간 까다로웠던 점은 char 하나 단위로 자르다보니 
점수가 10인 경우였는데 
첫번째 글자와 두번째 글자를 체크해서 10인경우
인덱스를 하나 더 옮겨주는것으로 구현을 했다. 
*/
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

int solution(string dartResult) {
	int answer = 0;
	stack<int> s;
	for (int i = 0; i < int(dartResult.size()); ++i) {
		//먼저 숫자가 10인가 체크해야함 
		if (dartResult[i] == '1' && dartResult[i+1] == '0') {
			++i;
			s.push(10);
			continue;
		}
		//0~9
		int point = dartResult[i] - '0';
		if (point >= 0 && point <= 9)
			s.push(point);
		//스타상인 경우 해당 점수와 바로 전에 얻은 점수를 각 2배로 만든다.
		if (dartResult[i] == '*') {
			if (s.size() >= 2) {
				int currPoint = s.top();
				s.pop();
				int prePoint = s.top();
				s.pop();
				s.push(prePoint * 2);
				s.push(currPoint * 2);
			}
			else {
				int currPoint = s.top();
				s.pop();
				s.push(currPoint * 2);
			}
		}
		//아차상인 경우 해당 점수는 마이너스가 된다 
		if (dartResult[i] == '#') {
			int currPoint = s.top();
			s.pop();
			s.push(-currPoint);
		}
		//Single : 1제곱이니까 그냥 continue;
		if (dartResult[i] == 'S') continue;
        //Double 2배
		if (dartResult[i] == 'D') {
			int currPoint = s.top();
			s.pop();
			s.push(currPoint * currPoint);
		}
        //Triple 3배 
		if (dartResult[i] == 'T') {
			int currPoint = s.top();
			s.pop();
			s.push(currPoint * currPoint * currPoint);
		}
	}
	while (!s.empty()) {
		answer += s.top();
		s.pop();
	}
	return answer;
}