/*
부동소수점 계산때문에 안된것으로 예측된다 2,3,18번만 실패함 
*/
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int solution(vector<string> lines);
pair<double, double> split(string log);
double translateSeconds(string time);
double calculateStartTime(double startTime, string processingTime);
int solution(vector<string> lines) {
	int answer = 0;
	//<시작시간, 종료시간> 쌍으로 저장
	vector<pair<double, double>> timeLog;
	for (int i = 0; i < int(lines.size()); ++i) {
		auto log = split(lines[i]);
		timeLog.push_back({ log.first, log.second });
	}
	//timeLog를 시간별로 정리한다. 
	sort(timeLog.begin(), timeLog.end());

	for (int i = 0; i < int(timeLog.size()); ++i) {
		int thoughoutStart = 0, thoughoutEnd = 0;
		double startTime = timeLog[i].first, endTime = timeLog[i].second;
		for (int j = 0; j < int(timeLog.size()); ++j) {
			auto log = timeLog[j];
			if ((log.first >= startTime && log.first < startTime +1) ||
				(log.second < startTime + 1 && log.second >= startTime))
				thoughoutStart++;
		}
		for (int j = 0; j < int(timeLog.size()); ++j) {
			auto log = timeLog[j];
			if ((log.first >= endTime && log.first < endTime + 1) ||
				(log.second < endTime + 1 && log.second >= endTime))
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
	double endTimeSecond = translateSeconds(endTimeString);
	string processingTime = string(strtok(NULL, delim));
	double startTime = calculateStartTime(endTimeSecond, processingTime);
	return { startTime, endTimeSecond };
}
//시간 문자열을 초로 변환한다. 
double translateSeconds(string time) {
	double ret = 0;
	auto begin = time.begin();
	double h = stod(string(begin, begin + 2));
	double m = stod(string(begin + 3, begin + 5));
	double s = stod(string(begin + 6, begin + 8));
	double ms = stod("0." + string(begin + 9, time.end()));
	ret = h * double(3600) + m * double(60) + s + ms;
	return ret;
}
//시작시간을 계산한다.
double calculateStartTime(double startTime, string processingTime) {
	double processingTimeDouble = stod(string(processingTime.begin(), processingTime.end() - 1));
	return startTime - processingTimeDouble + 0.001;
}