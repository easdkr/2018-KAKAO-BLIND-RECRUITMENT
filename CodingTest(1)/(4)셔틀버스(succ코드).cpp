/*
블로그를 참고해서 pq를 사용하여 구현한 코드이다. 
마지막셔틀에서 어떻게 시간을 관리하는가
(남아있는 크루가 m보다 작으면 그냥 정시에 도착,)
(m명보다 많으면 m번째 크루보다 1분 빨리 도착하기)
이거까지는 생각을했는데 결국 구현을 어떻게하는가에서 막혔다
이런류의 문제는 queue나 pq를 사용하도록 연습해야함!! 
그리고 시간을 쓰는 문제를 분으로 바꿔서 푸는방법,
다시 string으로 되돌리는법을 연습할 필요가 있다고 느낌
밑에 23번부터 시작하는 for문과 minuteToStringTime 함수 같은거 잘 숙지할것
*/
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
string minuteToStringTime(int minutes);
string solution(int n, int t, int m, vector<string> timetable) {
	string answer = "";
	int retMinute = 0;
	priority_queue<int, vector<int>, greater<int>> pq;
	//pq에 시간대별로 정렬 
	for (auto time : timetable) {
		int hour = (time[0] - '0') * 10 + time[1] - '0';
		int minute = (time[3] - '0') * 10 + time[4] - '0';
		pq.push(hour * 60 + minute);
	}
	//막차 직전시간대까지 pq처리 
	for (int i = 0; i < t * (n-1); i+= t) {
		int departureTime = 9 * 60 + i;
		int cnt = 0;
		//현재 시간에 탈 수 있는 크루들이 있으면
		//pq에서 pop 한다. 
		while (!pq.empty() && cnt < m) {
			int crew = pq.top();
			if (crew <= departureTime) {
				pq.pop();
				++cnt;
			}
			else break;
		}
	}
	//마지막 셔틀 처리 (m-1명까지만 우선 태운다)
	int lastSuttle = 9 * 60 + t * (n - 1);
	int cnt = 0;
	while (!pq.empty() && cnt < m - 1) {
		int crew = pq.top();
		if (crew <= lastSuttle) {
			pq.pop();
			++cnt;
		}
		else break;
	}
	//pq가 비었거나(남는 자리가 있거나), 나머지 크루들이 다 막차보다 늦게 온다면
	//정시에 도착해서 탄다
	if (pq.empty() || pq.top() > lastSuttle)
		retMinute = lastSuttle;
	//pq에 만약 더 탈 수 있는 크루가 남아있으면 그 크루보다 1분 일찍 온다
	else 
		retMinute = pq.top() - 1;
	
	answer = minuteToStringTime(retMinute);
	return answer;
}

string minuteToStringTime(int minutes) {
	string time;
	int hour = minutes / 60;
	int minute = minutes % 60;
	time += hour / 10 + '0';
	time += hour % 10 + '0';
	time += ":";
	time += minute / 10 + '0';
	time += minute % 10 + '0';
	return time;
}