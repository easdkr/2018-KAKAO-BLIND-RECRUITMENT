/*
따로 어떤 자료구조를 써야한다는 생각 없이 
string처리만으로 구현을 시도했는데 
main함수에 있는 예제의 경우에서 실패했다. 
마지막 직전 버스에서 타야할 인원이 m보다 많아서 남은경우
뒷버스로 밀리게 되는데 이걸 처리하기 번거로워서 
그냥 블로그참고하게 되었음! 
추가로 느낀점 : compare함수 작성할 때 a와 b의 값이 동일한 경우 false로 처리안하면 
                에러발생함 
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
string solution(int n, int t, int m, vector<string> timetable);
string minusOneMinute(string time);
string calculateTime(int n, int t);
bool compareTime(string& time1, string& time2);
int main(void) {
	int n = 2;
	int t = 1;
	int m = 2;
	vector<string> timetable = { "09:00","09:00","09:00","09:00"};
	cout << solution(n, t, m, timetable);
	return 0;
}

string solution(int n, int t, int m, vector<string> timetable) {
	string answer = "";
	//같은 시간대에 타는 크루 넣어주기 
	vector<string> crews;

	sort(timetable.begin(), timetable.end(), compareTime);
	//마지막 시간 구하기 
	string lastTime = calculateTime(n, t);
	//셔틀이 딱 한번만 오는 경우 
	if (n == 1) {
		for (int i = 0; i < int(timetable.size()); ++i) {
			string currTime = timetable[i];
			if (compareTime(currTime, lastTime)) {
				crews.push_back(currTime);
			}
		}
	}
	else {
		//마지막 시간대 직전 셔틀 도착시간 구하기
		string immediatelyBeforeTime = calculateTime(n - 1, t);
		for (int i = 0; i < int(timetable.size()); ++i) {
			string currTime = timetable[i];
			if (compareTime(immediatelyBeforeTime, currTime) && (compareTime(currTime, lastTime) || currTime == lastTime)) {
				crews.push_back(currTime);
			}
		}
	}
	//빈자리가 남는 경우는 정시에 도착
	if (crews.size() < m)
		answer = lastTime;
	//빈자리가 없는 경우 m-1번째 크루보다 1분먼저 도착하기
	else {
		string mCrew = crews[m - 1];
		answer = minusOneMinute(mCrew);
	}
	return answer;
}
string minusOneMinute(string time) {
	string hh, mm;
	hh = string(time.begin(), time.begin() + 2);
	//cout << "hh : " << hh << "\n";
	mm = string(time.end() - 2, time.end());
	//cout << "mm : " << mm << "\n";
	int h = atoi(hh.c_str());
	int m = atoi(mm.c_str());
	if (m == 0) {
		h--;
		m = 59;
	}
	else {
		m--;
	}
	hh = to_string(h);
	mm = to_string(m);
	if (hh.size() == 1)
		hh = "0" + hh;
	if (mm.size() == 1)
		mm = "0" + mm;
	return hh + ":" + mm;
}
string calculateTime(int n, int t) {
	string lastTime;
	string hh, mm;
	hh = to_string(9 + ((n-1) * t / 60));
	mm = to_string(((n-1) * t) % 60);
	if (hh.size() == 1)
		hh = "0" + hh;
	if (mm.size() == 1)
		mm = "0" + mm;
	lastTime = hh + ":" + mm;
	return lastTime;
}
//time1이 time2보다 빠르거나 같으면 true 늦으면 false;
bool compareTime(string& time1, string& time2) {
	int hour1 = atoi(string(time1.begin(), time1.begin() + 2).c_str());
	int hour2 = atoi(string(time2.begin(), time2.begin() + 2).c_str());
	int minute1 = atoi(string(time1.end() - 2, time1.end()).c_str());
	int minute2 = atoi(string(time2.end() - 2, time2.end()).c_str());
 	if (hour1 < hour2) return true;
	else if (hour1 > hour2) return false;
	else {
		if (minute1 < minute2) return true;
		else return false;
	}
}