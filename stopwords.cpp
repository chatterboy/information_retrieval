#include <cstdio>
#include <cstring>
#include <cctype>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
#define BUFFER_SIZE 128
#define WHITE_SPACE 0x20

FILE* fin;
FILE* fout;
char buf[BUFFER_SIZE]; // 문자열을 저장하기 위한 버퍼.
map<string,int> wtb;
set<string> swl;

void init_read_file(const char* fname) {
	// 읽기 모드로 파일을 연다.
	fin = fopen(fname, "r");
}

void free_read_file() {
	// 파일 닫기.
	fclose(fin);
}

// 파일에서 한 라인을 읽는 함수이다.
int read_line_file() {
	// buf를 0으로 초기화한다.
	memset(buf, 0, sizeof buf);
	// 한 라인을 파일로부터 읽어서 buf에 저장한다.
	if (fgets(buf, sizeof buf, fin) != NULL)
		return 0;
	return 1;
}

// 파일로부터 스탑워드 리스트들을 가져온다.
void get_stopwords_list_file() {
	while (!read_line_file()) {
		string w(buf);
		// 문자열 뒤 개행문자를 제거한다.
		while (w.back() == '\n')
			w.pop_back();
		swl.insert(w);
	}
}

void change_to_lower(string& w) {
	int n;
	n = w.size();
	for (int i = 0; i < n; i++)
		// i번째 문자가 알파벳이고 대문자이면 소문자로 바꾼다.
		if (isalpha(w[i]) && isupper(w[i]))
			w[i] = tolower(w[i]);
}

void get_words_line() {
	int n;
	bool flag;
	string w;
	n = strlen(buf);
	// buf에서 단어들을 찾은 후 테이블에 빈도수와 함께 저장한다.
	for (int i = 0; i < n; i++) {
		if (isalpha(buf[i]))
			w.push_back(buf[i]);
		else {
			// i번째가 white space이면 무조건 한 단어가 완성된 경우로 생각한다.
			// 다른 특수문자인 경우 i-1와 i+1번째 문자가 영문자이면 i번째도
			// 단어 안의 문자로 생각한다.
			flag = false;
			if (buf[i] != WHITE_SPACE)
				if ((i-1 >= 0 && isalpha(buf[i-1])) && (i+1 < n && isalpha(buf[i+1]))) {
					flag = true;
					w.push_back(buf[i]);
				}
			if (!flag) {
				// 만들어진 단어 w는 소문자로 변환 후 테이블에 빈도수와 같이 저장한다.
				if (!w.empty()) {
					change_to_lower(w);
					wtb[w]++;
				}
				w.clear();
			}
		}
	}
}

bool cmp(const pair<int,string>& a, const pair<int,string>& b) {
	if (a.first > b.first) return true;
	if (a.first < b.first) return false;
	return a.second < b.second;
}

// 빈도수를 기준으로 내림차순 정렬을 하고 빈도수가 같은 경우
// alphabetical order로 정렬한다.
void get_sorted_words(vector<pair<int,string>>& v) {
	for (auto it = wtb.begin(); it != wtb.end(); it++)
		v.push_back(make_pair(it->second, it->first));
	sort(v.begin(), v.end(), cmp);
}

void print_sorted_words() {
	vector<pair<int,string>> v;
	get_sorted_words(v);
	for (auto e : v)
		printf("%s %d\n", e.second.c_str(), e.first);
}

void print_sorted_words_file(const char* fname) {
	vector<pair<int,string>> v;
	get_sorted_words(v);
	fout = fopen(fname, "w");
	for (auto e : v)
		fprintf(fout, "%s %d\n", e.second.c_str(), e.first);
	fclose(fout);
}

void remove_stopwords_wtb() {
	for (auto sw : swl) {
		// wtb에서 stopword를 찾는다.
		auto p = wtb.find(sw);
		// 있다면 지운다.
		if (p != wtb.end())
			wtb.erase(p);
	}
}

// 주어진 텍스트 파일을 스탑워드 리스트 파일을 기반으로 분석하여
// 텍스트 파일의 단어 빈도 수를 기준으로 정렬(before_removing_stopwords.txt)
// 스탑워드를 제거한 후 남은 단어 빈도 수를 기준으로 정렬(after_removing_stopwords.txt)
// 결과를 확인할 수 있고 두 경우의 단어들의 수(compare_no_words.txt)를 비교할 수 있다.
int main() {
	init_read_file("Adventures_of_Huckleberry_Finn.txt");
	// 파일로부터 한 줄씩 읽어와서 단어 테이블을 생성한다.
	while (!read_line_file())
		get_words_line();
	free_read_file();

	init_read_file("default_stopwords_list.txt");
	get_stopwords_list_file();
	free_read_file();

	int before_sz = wtb.size();
	print_sorted_words_file("before_removing_stopwords.txt");

	remove_stopwords_wtb();

	int after_sz = wtb.size();
	print_sorted_words_file("after_removing_stopwords.txt");

	fout = fopen("compare_no_words.txt", "w");
	fprintf(fout, "number of words before removing stopwords: %d\n", before_sz);
	fprintf(fout, "number of words after removing stopwords: %d", after_sz);
	fclose(fout);
}