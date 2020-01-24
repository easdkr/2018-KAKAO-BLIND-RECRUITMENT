/*
LRU(가장 사용한지 오래된 페이지부터 교체)를 구현하는 문제였다
포인트는 2가지
1. LRU를 구현하는 것 
2. 대소문자 구분 없이 비교하는 것 

2번은 처음에 찾아보고 strcmpi 라는 대소문자 구분없이 비교하는 함수를 썼는데
VS에서만 돌아갔다.
-> 해결) 모든 문자열을 대문자로 다 변환하는 전처리를 한 후 LRU 실행 
1번은 그냥 벡터를 사용하여 구현했는데 캐시hit한 경우 
캐시 내부의 도시 순서를 바꿔줘야하는데 바꾸지 않고 구현했다. 
-> 해결) hit한 경우 해당 데이터를 지워주고 벡터 제일 뒤에 다시 넣어줌 

*/
#include <string>
#include <vector>
using namespace std;
string LowToUpper(string str);
int solution(int cacheSize, vector<string> cities) {
	//모두 대문자 글자로 바꿔주기
	for (int i = 0; i < cities.size(); ++i)
		cities[i] = LowToUpper(cities[i]);
	int answer = 0;
	//만약 캐시 사이즈가 0이면 
	vector<string> cache;
	for (string city : cities) {
		//캐시가 비어있는 경우
		if (cache.empty()) {
			answer += 5;
			if(cacheSize != 0)
				cache.push_back(city);
		}
		else { //캐시에 데이터가 있는 경우 
			bool cacheHit = false;
			for (int i = 0; i < int(cache.size()); ++i) {
				string data = cache[i];
				//캐시 히트한 경우 
				if (data == city) {
					cacheHit = true;
					answer += 1;
					cache.erase(cache.begin() + i);
					cache.push_back(data);
					break;
				}
			}
			
			//캐시 hit 못한 경우 
			if (!cacheHit) {
				//캐시가 가득 찬 경우
				if (cache.size() == cacheSize) {
					cache.erase(cache.begin());
					cache.push_back(city);
					answer += 5;
				}
				//캐시에 빈공간이 남은 경우
				else if (cache.size() < cacheSize) {
					cache.push_back(city);
					answer += 5;
				}
				//error (캐시에 캐시사이즈보다 더 많이 들어간 경우) 
				else {
					return -999;
				}
			}
		}
	}
	return answer;
}


string LowToUpper(string str) {
	for (int i = 0; i < int(str.size()); ++i) {
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] = str[i] + char(-32);
	}
	return str;
}