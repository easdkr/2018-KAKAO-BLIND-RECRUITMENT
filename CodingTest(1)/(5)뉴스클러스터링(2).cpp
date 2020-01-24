/*
집합 함수를 안쓰고 구현하는 방법이다. 
반복문으로 비교해가며 교집합의 개수를 구해주고
두 집합의 전체크기에서 교집합의 개수를 빼주어 합집합의 개수를 구한다. 
set_union이 없는 언어에서는 이런식으로 풀어야될것같다. 
*/
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const static int mulval = 65536;
int getInterSectionSize(vector<string>& mulset1, vector<string>& mulset2);
int getUnionSize(vector<string>& mulset1, vector<string>& mulset2);
vector<string> transferMultiSet(string& str);
string toUpperCase(string& str);
int solution(string str1, string str2) {
	int answer = 0;
	str1 = toUpperCase(str1);
	str2 = toUpperCase(str2);
	auto mulset1 = transferMultiSet(str1);
	auto mulset2 = transferMultiSet(str2);
	if (mulset1.size() == 0 && mulset2.size() == 0)
		return 1 * mulval;
	sort(mulset1.begin(), mulset1.end());
	sort(mulset2.begin(), mulset2.end());
	int interSetSize = getInterSectionSize(mulset1, mulset2);
	int unionSize = mulset1.size() + mulset2.size() - interSetSize;
	answer = ((double(interSetSize) / double(unionSize)) * double(mulval));
	return answer;
}
int getInterSectionSize(vector<string>& mulset1, vector<string>& mulset2) {
	int ret = 0;
	for (int iter1 = 0, iter2 = 0; iter1 < mulset1.size() && iter2 < mulset2.size();) {
		string elem1 = mulset1[iter1], elem2 = mulset2[iter2];
		int compareVal = elem1.compare(elem2);
		//같으면 개수추가 
		if (compareVal == 0) {
			ret++;
			iter1++;
			iter2++;
		}
		else if (compareVal < 0) iter1++;
		else iter2++;
	}
	return ret;
}
vector<string> transferMultiSet(string& str) {
	vector<string> ret;
	char upperA = 'A', upperZ = 'Z';
	for (int i = 1; i < int(str.size()); ++i) {
		char firstChar = str[i - 1], secondChar = str[i];
		if (firstChar < upperA || firstChar > upperZ ||
			secondChar < upperA || secondChar > upperZ)
			continue;
		string element;
		element.push_back(firstChar);
		element.push_back(secondChar);
		ret.push_back(element);
	}
	return ret;
}
string toUpperCase(string& str) {
	string ret = "";
	char lowerA = 'a', lowerZ = 'z';
	char lowToUp = 'A' - 'a';
	for (int i = 0; i < str.size(); ++i) {
		char c = str[i];
		//소문자이면 대문자로변환 
		if (c >= lowerA && c <= lowerZ)
			ret.push_back(char(c + lowToUp));
		//대문자, 특수문자나 공백인 경우 그냥 삽입
		else
			ret.push_back(c);
	}
	return ret;
}