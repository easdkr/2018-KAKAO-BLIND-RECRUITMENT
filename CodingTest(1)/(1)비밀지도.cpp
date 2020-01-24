/*
or 연산만 사용할줄 알면 풀수 있는 문제였다. 
주의할 점은 toBoard에서 #과 공백으로 이루어진 문자열을 만들 때
문자열의 길이가 n보다 작을 경우 앞에 공백을 추가해줘야한다. 
ex) 4 = 000100(2) = '()()()#()()' (n이 6인 경우)
*/
#include <string>
#include <vector>

using namespace std;
vector<string> toBoard(vector<int> arr);
vector<int> mergeArr(vector<int>& arr1, vector<int>& arr2);
vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
	vector<string> answer;
	vector<int> mergedArr = mergeArr(arr1, arr2);
	answer = toBoard(mergedArr);
	return answer;
}
//주어진 정수배열을 #(1) 과 ' '(0)으로 이루어진 문자열 배열을 반환한다.
vector<string> toBoard(vector<int> arr) {
	vector<string> ret;
	for (int i = 0; i < arr.size(); ++i) {
		int num = arr[i];
		string pass;
		while (num) {
			if (num % 2 == 0) pass = ' ' + pass;
			else pass = '#' + pass;
			num = num / 2;
		}
		//arr의 길이보다 짧다면 앞에 공백문자를 추가한다. 
        while (pass.size() != arr.size())
            pass = ' ' + pass;
		
		ret.push_back(pass);
	}
	return ret;
}
//arr1과 arr2를 or 연산한 결과를 반환한다. 
vector<int> mergeArr(vector<int>& arr1, vector<int>& arr2) {
	vector<int> ret;
	ret.resize(arr1.size());
	for (int i = 0; i < arr1.size(); ++i)
		ret[i] = arr1[i] | arr2[i];
	return ret;
}