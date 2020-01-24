/*
2개 문자열로 잘라서 합집합 교집합 개수를 구하는 문제이다
이 문제의 포인트는 중복을 허용한 다중집합인데 
set_union과 set_intersection은 중복을 허용하지 않는데 
그냥 쓰니까 풀렸다.. 뭐지? 
--> 찾아보니 set_union 함수가 완전 중복원소를 하나만 가지는건 아니고 
vec1이 {1,1,2} vec2가 {1,1,1,3}이면 
union = {1,1,1,2,3} 이렇게 됨 
즉 문제가 원하는 것과 똑같음 !

교집합도 마찬가지 
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
    //둘 다 다중집합의 원소가 없는 경우 
    if (mulset1.size() == 0 && mulset2.size() == 0)
        return 1 * mulval;
    sort(mulset1.begin(), mulset1.end());
    sort(mulset2.begin(), mulset2.end());
    int interSetSize = getInterSectionSize(mulset1, mulset2);
    int unionSize = getUnionSize(mulset1, mulset2);
    answer = ((double(interSetSize) / double(unionSize)) * double(mulval));
    return answer;
}
//교집합의 크기를 반환한다. 
int getInterSectionSize(vector<string>& mulset1, vector<string>& mulset2) {
    vector<string> interSet;
    interSet.resize(mulset1.size() + mulset2.size());
    auto iter = set_intersection(mulset1.begin(), mulset1.end(), mulset2.begin(), mulset2.end(), interSet.begin());
    interSet.erase(iter, interSet.end());
    return interSet.size();
}
//합집합의 크기를 반환한다.
int getUnionSize(vector<string>& mulset1, vector<string>& mulset2) {
    vector<string> unionSet;
    unionSet.resize(mulset1.size() + mulset2.size());
    auto iter = set_union(mulset1.begin(), mulset1.end(), mulset2.begin(), mulset2.end(), unionSet.begin());
    unionSet.erase(iter, unionSet.end());
    return unionSet.size();
}
//문자열을 두 글자씩 끊어 다중집합을 만들어 반환한다. 
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
//모든 문자열을 대문자로 변환한다. 
//특수문자나 공백인 경우 그냥 똑같이 삽입
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