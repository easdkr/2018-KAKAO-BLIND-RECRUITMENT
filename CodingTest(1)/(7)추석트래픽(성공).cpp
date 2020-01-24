/*트래픽이 겹치는 조건을 수정하여 성공하였다*/
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
pair<double, double> split(string log);
int translateSeconds(string time);
int calculateStartTime(int endTime, string processingTime);
int solution(vector<string> lines) {
	int answer = 0;
	//<시작시간, 종료시간> 쌍으로 저장
	vector<pair<int, int>> timeLog;
	for (int i = 0; i < int(lines.size()); ++i) {
		auto log = split(lines[i]);
		timeLog.push_back({ log.first, log.second });
	}
	//timeLog를 시간별로 정리한다. 
	sort(timeLog.begin(), timeLog.end());

	for (int i = 0; i < int(timeLog.size()); ++i) {
		int thoughoutStart = 0, thoughoutEnd = 0;
		int startTime = timeLog[i].first, endTime = timeLog[i].second;
		for (int j = 0; j < int(timeLog.size()); ++j) {
			auto log = timeLog[j];
			if(startTime <= log.second && startTime + 1000 > log.first)
				thoughoutStart++;

		}
		for (int j = 0; j < int(timeLog.size()); ++j) {
			auto log = timeLog[j];
			if (endTime <= log.second && endTime + 1000 > log.first)
				thoughoutEnd++;
		}
		answer = max(answer, thoughoutStart);
		answer = max(answer, thoughoutEnd);
	}
	return answer;
}
pair<double, double> split(string log) {
	const char* delim = " ";
	char* str = new char[log.size() + 1];
	std::strcpy(str, log.c_str());
	//날짜는 버림 
	char* token = strtok(str, delim);
	//트래픽 종료 시간
	string endTimeString = string(strtok(NULL, delim));
	int endTimeSecond = translateSeconds(endTimeString);
	string processingTime = string(strtok(NULL, delim));
	int startTime = calculateStartTime(endTimeSecond, processingTime);
	return { startTime, endTimeSecond };
}
//시간 문자열을 정수로 변환한다. 
int translateSeconds(string time) {
	int ret = 0;
	auto begin = time.begin();
	int h = stoi(string(begin, begin + 2))* 1000;
	int m = stoi(string(begin + 3, begin + 5)) * 1000;
	int s = stoi(string(begin + 6, begin + 8)) * 1000;
	int ms = stoi(string(begin + 9, time.end()));
	ret = h * 3600 + m * 60 + s + ms;
	return ret;
}
//시작시간을 계산한다.
int calculateStartTime(int endTime, string processingTime) {
	string ms = "";
	string s = "";
	int i;
	for (i = 0; i < processingTime.size(); ++i) {
		if (processingTime[i] == '.' || processingTime[i] == 's') break;
		else
			s.push_back(processingTime[i]);
	}
	if(i < processingTime.size()-1)
		ms = string(processingTime.begin() + i + 1, processingTime.end()-1);
	if (ms == "")
		return endTime - stoi(s) * 1000 + 1;
	else
		return endTime - (stoi(s) * 1000 + stoi(ms)) + 1;
}